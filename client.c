#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define broadcastIP "0.0.0.0"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data
 
void die(char * $socket){
	perror($socket);
	exit(1);
}
 
void main(){
	struct sockaddr_in broadcastAddr; // Make an endpoint
	int $socket;
	char buf[BUFLEN];
	char message[BUFLEN]={"{'message':'hello my dear'}"};
 
	if ( ($socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		die("socket");
	}

	int broadcastEnable=1;
	int socketNotAvailable = setsockopt($socket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

	if (socketNotAvailable) {
		perror("Error: Could not open set socket to broadcast mode");
		close($socket);
		return;
	}
	
	memset(&broadcastAddr, 0, sizeof broadcastAddr);
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
	broadcastAddr.sin_port = htons(PORT); // Set port 1900
 
	while(1){	  
		//send the message
		if (sendto($socket, message, strlen(message) , 0 , (struct sockaddr *) &broadcastAddr, sizeof broadcastAddr)==-1){
			die("sendto()");
		}
		 
		sleep(3);
	}
 
	close($socket);
}




