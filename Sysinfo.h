#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <linux/kernel.h>
#include <linux/sysinfo.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/utsname.h>   /* Header for 'uname'  */
#include <sys/time.h>
#include <string.h>


char * getKernelVersion();
float getTotalRam();
float getRamLoad();
int getNumOfCores();
int getSysUpTime();
int getClockSpeed();
double getCpuLoad();
