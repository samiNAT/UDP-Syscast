
/* this is the server program*/

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>  
#include <arpa/inet.h> 
#include <sys/socket.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8021   //The port on which to listen for incoming data

/* error  message function */  
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
	struct sockaddr_in si_me, si_other;

	int s, i, slen = sizeof(si_other) , recv_len;
	char buf[BUFLEN];

	/*creating a new udp socket*/
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		die("socket");

	/*resetting the struct buffer to zero*/
	memset((char *) &si_me, 0, sizeof(si_me));

	si_me.sin_family = AF_INET;/* assigning IPv4 address family*/
	si_me.sin_port = htons(PORT);/*broadcsting port*/
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);/* getting data from any client*/

	/*bind socket to port*/
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
		die("bind");

	/*keep listening for data*/
	while(1)
	{
		
		fflush(stdout);

		/*try to receive some data, this is a blocking call*/
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
			die("recvfrom()");

		printf(" %s\n" , buf);
		printf("\n");

	}

	close(s);
	return 0;
}
