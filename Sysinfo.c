#include"Sysinfo.h"
#define BUF_MAX 1024

struct utsname uname_ptr;
struct sysinfo sysinfo_ptr;

char * getKernelVersion() {
	uname(&uname_ptr);
	return uname_ptr.version;
}

float getTotalRam() {
	sysinfo(&sysinfo_ptr);

	const double megabyte = 1024 * 1024;

	return (sysinfo_ptr.totalram / megabyte);
}

float getRamLoad() {
	 sysinfo(&sysinfo_ptr);

	 float TotalRam = sysinfo_ptr.totalram;
	 float FreeRam =  sysinfo_ptr.freeram;
	 float UsedRam = TotalRam - FreeRam;
	 float RamUsage = UsedRam / TotalRam;
	 float BufferRam = sysinfo_ptr. bufferram;

	 return (BufferRam / TotalRam) * 100;
}

int getNumOfCores() {
	 return sysconf (_SC_NPROCESSORS_CONF);
}

int getSysUpTime() {
	 sysinfo(&sysinfo_ptr);	
	 return sysinfo_ptr.uptime;
}

int getClockSpeed() {
   FILE* fp;

   char buffer[10240]; 
   size_t bytes_read; 
   char* match; 
   float clock_speed; 

   /* Read the entire contents of /proc/cpuinfo into the buffer.  */ 
   fp = fopen ("/proc/cpuinfo", "r"); 
   bytes_read = fread (buffer, 1, sizeof (buffer), fp); 
   fclose (fp); 

   /* Bail if read failed or if buffer isn't big enough.  */ 
   if (bytes_read == 0 || bytes_read == sizeof (buffer)) 
     return 0; 

   /* NUL-terminate the text.  */ 
   buffer[bytes_read] == '\0'; 

   /* Locate the line that starts with "cpu MHz".  */ 
   match = strstr (buffer, "cpu MHz"); 

   if (match == NULL) 
     return 0; 

   /* Parse the line to extract the clock speed.  */ 
   sscanf (match, "cpu MHz  :  %f", &clock_speed); 

   return clock_speed;  
}

int readFields (FILE *fp, unsigned long long int *fields){
  int retval;
  char buffer[BUF_MAX];
 
  if (!fgets (buffer, BUF_MAX, fp))
  { perror ("Error"); }
  retval = sscanf (buffer,
  			"cpu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu", 
			&fields[0], 
			&fields[1], 
			&fields[2], 
			&fields[3], 
			&fields[4], 
			&fields[5], 
			&fields[6], 
			&fields[7], 
			&fields[8], 
			&fields[9]); 

  if (retval < 4){ /* Atleast 4 fields is to be read */
	fprintf (stderr, "Error reading /proc/stat cpu field\n");
	return 0;
  }

  return 1;
}
 
double getCpuLoad() {
	FILE *fp;

	unsigned long long int fields[10], total_tick, total_tick_old, idle, idle_old, del_total_tick, del_idle;
	int update_cycle = 0, i;
	double percent_usage;

	fp = fopen ("/proc/stat", "r");
	if (fp == NULL) {
		perror ("Error");
	}
 
	if (!readFields (fp, fields)) {
		return 0;
	}

	for (i=0, total_tick = 0; i<10; i++) {
		total_tick += fields[i];
	}

	idle = fields[3]; /* idle ticks index */
	sleep (1);
	total_tick_old = total_tick;
	idle_old = idle;

	fseek (fp, 0, SEEK_SET);
	fflush (fp);

	if (!readFields (fp, fields)) {
		return 0;
	}

	for (i=0, total_tick = 0; i<10; i++){
		total_tick += fields[i];
	}

	idle = fields[3];
	del_total_tick = total_tick - total_tick_old;
	del_idle = idle - idle_old;

	percent_usage = ((del_total_tick - del_idle) / (double) del_total_tick) * 100; /* 3 is index of idle time */
	update_cycle++;
 
  fclose (fp);
 
  return percent_usage;
}