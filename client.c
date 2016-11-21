
/* this is the client program*/

#include <stdio.h> 
#include <string.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include "funcs.h"

#define broadcastIP "0.0.0.0" /*broadcasting ip*/
#define BUFLEN 512  //Max length of buffer
#define PORT 8021   //The port on which to send data


/* error creating socket message function */ 
void die(char *sock)
{
    perror(sock);
    exit(1);
}
 
int main(void)
{
	int sock;
	char *module,*cpuClockSpeed;
	char message[BUFLEN];
	struct sockaddr_in broadcastAddr; // Make an endpoint

        /*creating a new udp socket*/
	if ( (sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		die("socket");

	/*configuring broadcast option for the socket*/	
	int broadcastEnable=1;
	int ret=setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
	if (ret) {
		perror("Error: Could not open set socket to broadcast mode");
		close(sock);
		return 1;
	}
        
	memset(&broadcastAddr, 0, sizeof broadcastAddr); /*resetting the struct buffer to zero*/
	broadcastAddr.sin_family = AF_INET ;/* assigning IPv4 address family*/
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
	broadcastAddr.sin_port = htons(PORT); /*broadcsting port*/

        /*keep sending data*/
	while(1)
	{       /* calling the different system info functions and copying the returned values to message buffer respectively "similar to scanf"*/
		snprintf(message,sizeof message,"'cpuModel': '%s', 'clockSpeed': '%s', 'numOfCores': '%d', 'cpuLoad': '%3.2lf%%' 'ramSize': '%0.1f', 'ramLoad': '%0.2f%%', 'uptime': '%d s', 'kernelVersion': '%s'",
				module=getCpuModel(),cpuClockSpeed=getClockSpeed(),getNumOfCores(),\
				getCpuLoad(),getTotalRam(),getRamLoad(),getSysUpTime(),getKernelVersion());

		/*sending the data in the message buffer*/
		if (sendto(sock, message, strlen(message) , 0 , (struct sockaddr *) &broadcastAddr, sizeof broadcastAddr)==-1)
			die("sendto()");
		free(module);
		free(cpuClockSpeed);
		sleep(2);
	}

	close(sock);
	return 0;
}
