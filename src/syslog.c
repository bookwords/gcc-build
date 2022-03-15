
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
#include "os_api.h"

/***********************************macro*************************************/

/***********************************struct************************************/

/*********************************declaration*********************************/

/*********************************global data*********************************/
FILE *g_sys_log_file = NULL;
unsigned long log_size = 0;
#if 0
static int default_dbg_level = HL_NOTICE;
#else
static int default_dbg_level = HL_DEBUG;
#endif

#if 0
#define LM_APP     0    /* 1     */
#define LM_SYS     1    /* 2     */
#define LM_USB     2    /* 4     */
#define LM_WEB    3    /* 8     */
#define LM_WIFI   4    /* 16    */
#define LM_MISC   5    /* 32    */
#endif

char *mode_str[] =
{
"app",  /* 0 */
"sys",  /* 1 */
"usb",  /* 2 */
"web", /* 3 */
"wifi", /* 4 */
"misc", /* 5 */
"sta", /* 6 */
"ap",  /* 7 */
"user",  /* 8 */
"smtp", /* 9 */
"cap",  /* 10 */
"trace",/* 11 */
"http", /* 12 */
"rtp",  /* 13 */
"igmp", /* 14 */
"led",  /* 15 */
"ntp",  /* 16 */
"echo", /* 17 */
NULL    /* 18 */
};

char *log_hdr[8]=
{
"Emergency",
"Alert",
"Critical",
"Error",
"Warning",
"Notice",
"Info",
"Debug"
};


int set_debug_level(char *level)
{
    /* P_T_POINT_PRO_CFG p_cfg; */

    int retval = 0;

    if(NULL == level)
    {
        return 2;
    }

    /* p_cfg = get_pointpro_cfg();
    if(p_cfg)
    {
        if(strstr(level, "debug"))
        {
            p_cfg->log_level = HXNT_LOG_DEBUG;
        }
        else if(strstr(level, "info"))
        {
            p_cfg->log_level = HXNT_LOG_INFO;
        }
        else if(strstr(level, "notice"))
        {
            p_cfg->log_level = HXNT_LOG_NOTICE;
        }
        else if(strstr(level, "err"))
        {
            p_cfg->log_level = HXNT_LOG_ERR;
        }
        else if(strstr(level, "alert"))
        {
            p_cfg->log_level = HXNT_LOG_ALERT;
        }
        else if(strstr(level, "emerg"))
        {
            p_cfg->log_level = HXNT_LOG_EMERG;
        }
    } */
    /* else */
    {
        if(strstr(level, "debug"))
        {
            default_dbg_level = HL_DEBUG;
        }
        else if(strstr(level, "info"))
        {
            default_dbg_level = HL_INFO;
        }
        else if(strstr(level, "notice"))
        {
            default_dbg_level = HL_NOTICE;
        }
        else if(strstr(level, "err"))
        {
            default_dbg_level = HL_ERR;
        }
        else if(strstr(level, "alert"))
        {
            default_dbg_level = HL_ALERT;
        }
        else if(strstr(level, "emerg"))
        {
            default_dbg_level = HL_EMERG;
        }
        else
        {
            retval = 1;
        }
    }

    return retval;
}

void log_sys_level(unsigned int level, unsigned int module, char *format, ...)
{
    va_list val;
    char buffer[MAX_LOG_BUF], timestr[40];
    time_t t;
    struct tm this_tm;

    /* if(level < sys_log_level)
    {
        return;
    }

    if(pno != 0)
    {
        return;
    }

    if(module == LOG_MODULE_ICMP)
    {
        return;
    } */

    if((level < 0)||(level > default_dbg_level))
    {
        return ;
    }

    if(g_sys_log_file)
    {
        va_start(val, format);
        vsnprintf(buffer, sizeof(buffer), format, val);
        va_end(val);

        fseek(g_sys_log_file, 0, SEEK_END);
        time(&t);
        localtime_r(&t, &this_tm);
        strftime(timestr, sizeof(timestr), "%d %H:%M:%S", &this_tm);

        /* fprintf(g_sys_log_file, "**EEE**: %s:%s",
                timestr, buffer); */
        fprintf(g_sys_log_file, "%s [%s] %s : %s", timestr, mode_str[module], log_hdr[level], buffer);

        fflush(g_sys_log_file);
    }
}


int init_sys_file(char *logfile)
{
    /* mode_t mode = S_IRWXU|S_IRGRP |S_IWGRP|S_IROTH|S_IWOTH;
    g_sys_log_fd = open(p_File, O_CREAT|O_SYNC|O_RDWR, mode); */
    char bakname[256];
    char *p_name;
    char *p_bakname;
    int max_log = 10;
    int loop;
    char fileo[64], filen[64];

    log_size = 0;

    if(NULL == logfile)
    {
        g_sys_log_file = stderr;
        return 0;
    }


    for(loop = max_log-2; loop >= 0; loop--)
    {
        snprintf(fileo, sizeof(fileo), "%s.%u", logfile, loop);
        if(check_file_exist(fileo))
        {
            snprintf(filen, sizeof(filen), "%s.%u", logfile, loop+1);
            if(check_file_exist(filen))
            {
                remove(filen);
            }
            rename(fileo, filen);
        }
        #if 0
        if(check_file_exist(logfile))
        {
            snprintf(filebak, sizeof(filebak), "%s.bak", logfile);
            remove(filebak);
            rename(logfile, filebak);
            /* printf("File exist.\n"); */
        }
        /* else
        {
            printf("File No exist.\n");
        } */
        #endif
    }

    if(check_file_exist(logfile))
    {
        snprintf(filen, sizeof(filen), "%s.%u", logfile, 0);
        remove(filen);
        rename(logfile, filen);
        /* printf("File exist.\n"); */
    }

    /* snprintf(bakname, sizeof(bakname), "%s.1", p_File);
    rename(p_File, bakname); */

    if(!(g_sys_log_file = fopen(logfile, "a")))
    {
        printf("%s:Fail open %s.\n", __func__, logfile);
        return -1;
    }

    /* log_sys_info("初始化: %s\n", __func__); */
    return 0;
}


int uninit_sys_file(void)
{
    int retval = 0;
    if(g_sys_log_file)
    {
        fclose(g_sys_log_file);
    }

    return retval;

}



