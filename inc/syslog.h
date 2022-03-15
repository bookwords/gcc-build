
#ifndef _H_SYSLOG_H_ /* #ifndef _H_SYSLOG_H_ */
#define _H_SYSLOG_H_
/**********************************header************************************/

/***********************************macro*************************************/
/* #define LOG_FILE        (1) */
#define LOG_TERMINAL    (2)

#define LOG_EMERG   0
#define LOG_ALERT   2
#define LOG_CRIT    4
#define LOG_ERR     8
#define LOG_WARNING 16
#define LOG_NOTICE  32
#define LOG_INFO    64
#define LOG_DEBUG   128

#define MAX_MAP_SIZE        10485760

#define LM_APP     0    /* 1     */
#define LM_SYS     1    /* 2     */
#define LM_USB     2    /* 4     */
#define LM_WEB    3    /* 8     */
#define LM_WIFI   4    /* 16    */
#define LM_MISC   5    /* 32    */
#define LM_STA    6    /* 64    */
#define LM_AP      7    /* 128   */

#define LM_USER     8    /* 256   */
#define LM_SMTP    9    /* 512   */
#define LM_CAP     10   /* 1024  */
#define LM_TRACE   11   /* 2048  */
#define LM_HTTP    12   /* 4096  */
#define LM_RTP     13   /* 8192  */
#define LM_IGMP    14   /* 16384 */
#define LM_LED     15   /* 32768 */
#define LM_NTP     16   /* 65536 */
#define LM_ECHO    17   /* 65536 */

#define PRO_LOG_EMERG   0   /* systemis unusable */
#define PRO_LOG_ALERT   1   /* actionmust be taken immediately */
#define PRO_LOG_CRIT    2   /* critical conditions */
#define PRO_LOG_ERR     3   /* errorconditions */
#define PRO_LOG_WARNING 4   /* warning conditions */
#define PRO_LOG_NOTICE  5   /* normalbut significant */
#define PRO_LOG_INFO    6   /* informational */
#define PRO_LOG_DEBUG   7   /* debug-level messages */

#define HL_EMERG   0   /* systemis unusable */
#define HL_ALERT   1   /* actionmust be taken immediately */
#define HL_CRIT    2   /* critical conditions */
#define HL_ERR     3   /* errorconditions */
#define HL_WARNING 4   /* warning conditions */
#define HL_NOTICE  5   /* normalbut significant */
#define HL_INFO    6   /* informational */
#define HL_DEBUG   7   /* debug-level messages */

#define MAX_LOG_BUF 1600

/***********************************struct************************************/

/*********************************declaration*********************************/
int init_sys_file(char *logfile);
void log_sys_info_r(char *format, ...);
void log_sys_level(unsigned int level, unsigned int module, char *format, ...);
int set_debug_level(char *level);
int uninit_sys_file(void);

/*********************************global data*********************************/

/*********************************definition**********************************/

#endif /* #ifndef _H_SYSLOG_H_ */

/* end of file syslog.h */

