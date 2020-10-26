#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>

typedef enum{
	ERROR=0,
	WARNING=1,
	INFO=2,
	DEBUG=3,
	DEFAULT=4,
} Print_Level;

extern Print_Level debug_level;
#define Log(t_level,args...)    if(t_level<=debug_level)										\
								{																\
									 printf("[%s] [%s] [%d]",__FILE__,__FUNCTION__,__LINE__);	\
									 myprintf(t_level,args);									\
								}    
                                       
int myprintf(Print_Level t_level,const char *fmt, ...);
#endif /*__LOG_H__*/
