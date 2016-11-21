/*headers file*/
#ifndef __FUNCS_H_
#define __FUNCS_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <linux/kernel.h>
#include <linux/sysinfo.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/utsname.h> 
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>


char * getKernelVersion();
float getTotalRam();
float getRamLoad();
int getNumOfCores();
int getSysUpTime();
char* getClockSpeed();
double getCpuLoad();
char* getCpuModel(); 

#endif
