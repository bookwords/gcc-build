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
#include "os_api.h"

/***********************************macro*************************************/

/***********************************struct************************************/

/*********************************declaration*********************************/


/*********************************global data*********************************/


int check_file_exist(char *dname)
{
    int retval;

    if(NULL== dname)
    {
        return 0;
    }

    retval = access(dname, F_OK);

    return (0 == retval);
}
