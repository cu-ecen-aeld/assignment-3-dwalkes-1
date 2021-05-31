
/**
 * @file writer.c
 * @brief This file consists of code that counts the number of files in a specified directory
 * and searches the string specified in all the files and keeps a count of ther siearched string.
 * The command line parameters taken are: 1)Directory Path and 2)the string to be searched.
 *
 * @author Siddhant Jajoo
 * @date 07/05/2019
 * @copyright Copyright (c) 2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[])
{
	openlog(NULL,0,LOG_USER);	
	if(argc != 3)
	{
		printf("Invalid Number of arguments.\n1) File Path.\n2) String to be entered in the file.\n");
		syslog(LOG_ERR,"Invalid Number of arguments: %d",argc);
		exit(EXIT_FAILURE);
	} else {

		FILE *fhandle;
		time_t ctime;
		struct tm *timeinfo;
		const char *filename=argv[1];
		const char *writestr=argv[2];

		time(&ctime);
		timeinfo = localtime(&ctime);	


		fhandle = fopen(filename, "w");
		if(fhandle == NULL)
		{
			perror("ERROR: Could not open file; fopen().\n");
			syslog(LOG_ERR,"Could not open file %s for write; fopen(), error was %d (%s)",filename,errno,strerror(errno));
			exit(EXIT_FAILURE);
		}
		syslog(LOG_DEBUG,"Writing %s to %s",writestr,filename);

		fprintf(fhandle, "%s.\n",writestr);
		fprintf(fhandle, "Github Username: aesd-classroom-default.\n");
		fprintf(fhandle, "Current Date and Time: %s\n", asctime(timeinfo));


		fclose(fhandle);
	}
	return 0;
}