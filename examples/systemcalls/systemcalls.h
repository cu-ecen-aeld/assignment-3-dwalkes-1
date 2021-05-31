#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


bool do_system(const char *cmd);

bool do_exec(int count, ...);

bool do_exec_redirect(const char *outputfile, int count, ...);
