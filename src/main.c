/**********************************************************************
* File: main.c
* author: guonaij
* descr:  simple make process.
* 
**********************************************************************/
/**********************************header************************************/
#include <stdio.h>
#include <string.h>
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
#include "os_api.h"
#include "main.h"


/***********************************macro*************************************/

/***********************************struct************************************/

/*********************************declaration*********************************/

/*********************************global data*********************************/

int main(int argc, char *argv[])
{
    int retval = 0;

    //init log
    init_sys_file(log_file);

    //wirte log
    log_sys_level(HL_DEBUG, LM_SYS, "%s", "Congratulations.\n");


    //close log
    uninit_sys_file();

    return retval;
}

