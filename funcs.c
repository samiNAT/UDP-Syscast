#include "funcs.h"

/*declaring pointers to <sys/utsname.h> <sys/sysinfo> libraies*/

struct utsname uname_ptr;
struct sysinfo sysinfo_ptr;
/*------------------------------------------------------------------------------------------------*/
/* Kernel version function */

char * getKernelVersion() {
	uname(&uname_ptr);
	return uname_ptr.version;
}
/*------------------------------------------------------------------------------------------------*/
/* Total Ram funtion */

float getTotalRam() {
	sysinfo(&sysinfo_ptr);
	const double megabyte = 1024 * 1024;
	return (sysinfo_ptr.totalram / megabyte);
}
/*------------------------------------------------------------------------------------------------*/
/* Ram load function */

float getRamLoad() {
	FILE* fp; 
	char buffer[10240]; 
	size_t bytes_read; 
	char *match_Available,*match_MemTotal;
	float Available,MemTotal;

        /*opening proc file in linux to get the relevant information*/

	fp = fopen ("/proc/meminfo", "r"); 

        /*reading data and storing it in buffer*/

	bytes_read = fread (buffer, 1, sizeof (buffer), fp); 
	fclose(fp);
 
	/* Bailing if read failed or if buffer isn't big enough.  */ 

	if (bytes_read == 0 || bytes_read == sizeof (buffer)) 
		return 0;

	/* Locating the lines that start with the requested data */ 
	match_Available = strstr(buffer,"Available");
	match_MemTotal = strstr (buffer, "MemTotal");
	sscanf (match_MemTotal, "MemTotal    :    %f", &MemTotal); 
	sscanf (match_Available, "Available  :    %f", &Available);	
	return (1-((Available) / MemTotal)) * 100; /* memory load calculation*/

/*------------------------------------------------------------------------------------------------*/

/* Number of cores function*/
}

int getNumOfCores() {
	return sysconf (_SC_NPROCESSORS_CONF);
}

/*------------------------------------------------------------------------------------------------*/

/* System uptime function */
int getSysUpTime() {
	sysinfo(&sysinfo_ptr);	
	return sysinfo_ptr.uptime;
}
/*------------------------------------------------------------------------------------------------*/

/*Clock speed function*/
char* getClockSpeed() 
{
	FILE* fp; 
	char buffer[10240]; 
	size_t bytes_read; 
	char* match; 
	char cpu_clock[10];
	char *ptr; 

	/* Read the entire contents of /proc/cpuinfo into the buffer.  */ 

	fp = fopen ("/proc/cpuinfo", "r"); 
	bytes_read = fread (buffer, 1, sizeof (buffer), fp); 
	fclose(fp); 

	/* Bail if read failed or if buffer isn't big enough.  */ 

	if (bytes_read == 0 || bytes_read == sizeof (buffer)) 
		return NULL;

	/* Locate the line that starts with "model name".  */ 

	match = strstr (buffer, "model name"); 
	if (match == NULL) 
		return NULL; 

	/* Parse the line to extract the clock speed.  */ 

	sscanf (match, "model name      :    %*s %*s %*s %*s %*s %s", &cpu_clock);
	ptr=(char*)malloc(strlen(cpu_clock)+1);
	strcpy(ptr,cpu_clock);
	return ptr;
} 
/*-------------------------------------------------------------------------------------------------*/

/*Cpu load function*/

int readFields (FILE *fp, unsigned long long int *fields){/*this functon stores cpu times into Fields buffer */
	int BUF_MAX = 1024;
	char buffer[BUF_MAX];

	if (!fgets (buffer, BUF_MAX, fp))
		perror ("Error");
	sscanf (buffer,
	"cpu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu",     
	&fields[0],/*user*/
	&fields[1],/*nice*/ 
	&fields[2],/*system*/ 
	&fields[3],/*idle*/ 
	&fields[4],/*iowait*/ 
	&fields[5],/*irq*/
	&fields[6],/*softirq*/ 
	&fields[7],/*steel*/ 
	&fields[8],/*guest*/ 
	&fields[9]);/*guest_nice*/ 
}

double getCpuLoad() {
	FILE *fp;
	unsigned long long int fields[10], totalTime, totalTime_old, idle, idle_old, sub_totalTime, sub_idle;
	int  i;
	double percent_usage;
        /* Read the entire contents of /proc/stat into the buffer.  */ 
	fp = fopen ("/proc/stat", "r");
	if (fp == NULL)
		perror ("Error");
         /*calling read function in order to get cpu times stored*/ 
	if (!readFields (fp, fields))
		return -1;
        /*calculating the total cpu time*/
	for (i=0,totalTime=0; i<10; i++)
		totalTime += fields[i];

	idle = fields[3]; /* idle ticks index */
	/*sleeping for 1 sec in order to get new cpu time*/
	sleep (1);
	totalTime_old = totalTime;
	idle_old = idle;

        /*going back to the begining of the file*/
	fseek (fp, 0, SEEK_SET);
	fflush (fp);

        /*calling read function again in order to get the new cpu time*/
	if (!readFields (fp, fields))
		return -1;

        /*recaculating the cpu total time*/ 
	for (i=0,totalTime=0; i<10; i++)
		totalTime += fields[i];

        /*cpu load calculating equations*/
	idle = fields[3];
	sub_totalTime = totalTime - totalTime_old;
	sub_idle = idle - idle_old;

	percent_usage = ((sub_totalTime - sub_idle) / (double)sub_totalTime  * 100);


	fclose (fp);

	return percent_usage;/*returning the cpu load perentage*/
}
/*--------------------------------------------------------------------------------------------------*/
char* getCpuModel() 
{
	FILE* fp; 
	char buffer[10240]; 
	size_t bytes_read; 
	char* match; 
	char model_name[10];
	char *ptr; 

	/* Read the entire contents of /proc/cpuinfo into the buffer.  */ 
	fp = fopen ("/proc/cpuinfo", "r"); 
	bytes_read = fread (buffer, 1, sizeof (buffer), fp); 
	fclose(fp); 

	/* Bail if read failed or if buffer isn't big enough.  */ 

	if (bytes_read == 0 || bytes_read == sizeof (buffer)) 
		return NULL;

	/* Locate the line that starts with "model name".  */ 

	match = strstr (buffer, "model name"); 
	
	if (match == NULL) 
		return NULL; 

	/* Parse the line to extract the clock speed.  */ 

	sscanf (match, "model name      :        %s", &model_name);
	ptr=(char*)malloc(strlen(model_name)+1);
	strcpy(ptr,model_name);
	return ptr;
}
