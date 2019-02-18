/*
 	ActernaBNC: Bouncer tool to use the Acterna TestPad FST-2802 with
                    with a Linux Loopback Device

	(C) 2011 - Unilogic Networks B.V.
		   Cliff Albert <cliff@unilogicnetworks.net>

	License  - BEERWARE+ (buy me a beer, but not schultenbrau, amstel, heineken, oranjeboom
	                      lindeboom, oettinger, grolsch, bavaria, dommelsch or any beer brewn
			      in the United States of America)

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXFRAME_SIZE 1514
#define SND_FRAME_LEN 1480

#define VERSION "0.3.1"

int main(int argc, char *argv[])
{

/*
 DEFINITIONS 
*/

int s; /*socketdescriptor*/

struct sockaddr_storage peer_addr;
socklen_t peer_addr_len;
ssize_t returnsendto;

unsigned char* sbuffer = (unsigned char*)malloc(SND_FRAME_LEN);
unsigned char* buffer = (unsigned char*)malloc(MAXFRAME_SIZE);

int length = 0; /*length of the received frame*/

struct sockaddr_in si_other;
socklen_t slen=sizeof(si_other);

/*
 CODE
*/

printf ("Acterna TestPad FST-2802 Linux Loopback\n");
printf ("(c) 2011 Unilogic Networks B.V.\n");
printf ("Release: August 12th 2011\n");

if (argc != 2) {
printf ("Usage: acternabnc <ip remote unit>\n");
exit(EXIT_FAILURE);
}

printf ("Remote Tester IP: %s \n",argv[1]);


s = socket(AF_INET, SOCK_RAW, 0xFE);
if (s == -1) { printf("ERROR BINDING SOCKET...\n"); exit(0); }

memset(buffer, '\0', MAXFRAME_SIZE);
memset(sbuffer, '\0', SND_FRAME_LEN);

memset((char *) &si_other, 0, sizeof(si_other));
si_other.sin_family = AF_INET;
si_other.sin_port = 0xFE;
inet_aton(argv[1], &si_other.sin_addr);

peer_addr_len = sizeof(struct sockaddr_storage);

while(1){

	length = recvfrom(s, buffer, MAXFRAME_SIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);

/*
	printf ("Length of Packet: %i\n",length);
*/

	sbuffer = buffer+20;

	returnsendto = sendto(s, sbuffer, length - 20, 0, (struct sockaddr *) &si_other, slen);

	memset(buffer, '\0', MAXFRAME_SIZE);

}

close(s);

}
