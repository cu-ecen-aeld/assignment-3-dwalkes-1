#include "systemcalls.h"

/**
 * @param cmd the command to execute with system()
 * @return true if the commands in ... with arguments @param arguments were executed 
 *   successfully using the system() call, false if an error occurred, 
 *   either in invocation of the system() command, or if a non-zero return 
 *   value was returned by the command issued in @param.
*/
bool do_system(const char *cmd)
{
    bool success =  false;
    int ret = system(cmd);

    if ( ret != -1 && WEXITSTATUS(ret) == 0 ) {
        success = true;
    }
   
    return success;
}

/**
 * @param command - the command array argv
 * @param redirect_file_may_be_null - when not null, the filename to use as
 * output redirect.
 * @return true on success, false on error
 */
static bool do_exec_redirect_to_file(char **command, const char *redirect_file_may_be_null)
{
    bool success = false;
    int pid; 
    if ((pid = fork()) < 0) {     /* fork a child process           */
        printf("*** ERROR: forking child process failed with %s\n",strerror(errno));
    } else {
        if(pid == 0){
            int ret;
            /**
             * This is the child process
             * Assuming we can successfully execute the command, the exit code
             * will be the exit from the command.
             * However, if we can't successfully start the command we will
             * need to exit with failure here so the parent catches the failed
             * exit code
             */
            if( redirect_file_may_be_null != NULL ) {
                int fd = open(redirect_file_may_be_null, O_WRONLY|O_TRUNC|O_CREAT, 0644);
                if (fd < 0)
                {
                    printf("open failed for file %s",redirect_file_may_be_null);
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd, 1) < 0)
                {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }
            if ((ret = execv(command[0], command)) < 0) {     /* execute the command  */
                printf("*** ERROR: exec failed with return value %d\n",ret);
                fprintf(stderr, "execv: %s error: %s\n", command[0], strerror(errno));
                exit(EXIT_FAILURE);
            }
       } else {          /* for the parent process:         */
            int status;
            int return_value;
            while (wait(&status) != pid)       /* wait for completion  */
                ;
            return_value = WEXITSTATUS(status);
            if(return_value != 0) {
                printf("Command %s returned not zero exit code %d\n",command[0],return_value);
            } else {
                success = true;
            }
        }
    }
    return success;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the 
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/
bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    bool success = false;
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    if( count > 0 ) {
        success = do_exec_redirect_to_file(command,NULL);
    }

    va_end(args);
    return success;
}


/**
* @param outputfile - The full path to the file to write with command output.  
*   This file will be closed at completion of the function call.
* for documentation of all other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    bool success = false;
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    if( count > 0 ) {
        success = do_exec_redirect_to_file(command,outputfile);
    }


    va_end(args);
    return success;
}
