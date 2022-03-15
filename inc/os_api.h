#ifndef _H_OS_API_H_
#define _H_OS_API_H_

/**********************************header************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <time.h>
#include "syslog.h"

/***********************************macro*************************************/

/***********************************struct************************************/

/*********************************declaration*********************************/

int check_file_exist(char *dname);

/*********************************global data*********************************/

#endif

/* end of file */
