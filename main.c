#include <stdio.h>
#include <string.h>
#include "Sysinfo.h"

void main() {
	char message[2000];

	snprintf(
		message,
		sizeof message,
		"'kernelVersion': '%s', 'ramSize': '%0.1f', 'ramLoad': '%0.1f%%', 'numOfCores': '%d', 'uptime': '%d s', 'clockSpeed': '%d Mhz', 'cpuLoad': '%3.2lf Mhz'",
		getKernelVersion(),
		getTotalRam(),
		getRamLoad(),
		getNumOfCores(),
		getSysUpTime(),
		getClockSpeed(),
		getCpuLoad()
	);

	printf("{%s} \n", message);
}