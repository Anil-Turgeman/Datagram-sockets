#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
 

void printsin(struct sockaddr_in *sin, char *pname, char* msg) {
	printf("%s\n", pname);	
	printf("%s", msg);	
	printf("ip= %s, port= %d\n ", inet_ntoa(sin->sin_addr), sin->sin_port);//inet_ntoa returns the address of a client side
	//-- port: sin->sin_port (host integer type) 
	//-- IP: sin->sin_addr (IP in dotted-decimal notation) 
	printf("\n");
}

 
int main(int argc, char *argv[]){
	int socket_fd, cc, fsize;
	struct sockaddr_in  s_in, from;
	char get_message[1000];
	char send_message[] = "Test-Server";
	struct { char head; u_long  body; char tail;} msg;//struct that holds the information about the IP of the socket.
 
	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Socket creation with IPv4 protocol and TCP protocol.
 
	bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    *///the function erases the data in the n bytes of the memory.
 
	s_in.sin_family = (short)AF_INET;//Insert IPv4 to s_in.
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
	s_in.sin_port = htons((u_short)0x3333);//Insert to s_in a port number of short type.
 
	printsin( &s_in, "RECV_UDP", "Local socket is "); 
	fflush(stdout);
 
	bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//Set the port and address with the socket.
 
	for(;;) {
		fsize = sizeof(from);
		cc = recvfrom(socket_fd,&get_message,sizeof(get_message),0,(struct sockaddr *)&from,&fsize);//receives data on a socket named by descriptor socket.
		sendto(socket_fd,&send_message,sizeof(get_message),0,(struct sockaddr *)&from,fsize);
		printsin(&from, "recv_udp: ", "Packet from: ");
		printf("Got data ::%s\n",get_message); 
		fflush(stdout);
  	}
  	return 0;
}
