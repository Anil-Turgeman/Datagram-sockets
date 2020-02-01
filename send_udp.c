#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; u_long body; char tail; } msgbuf;
  char send_message[] = "Test-Anil";
  char get_message[1000];

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Socket creation with IPv4 protocol and TCP protocol.
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this *///the function erases the first sizeof chars of s_in and insert '0' instead.
  hostptr = gethostbyname(argv[1]);//Retrieves host information corresponding to a host name.
  dest.sin_family = (short) AF_INET;//Insert the IP adderss to the s_in.
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);//Copy the dest address to our hostent struct.
  dest.sin_port = htons((u_short)0x3333);//Insert the port to the struct with the information about the socket using the network to host short function.

  msgbuf.head = '<';
  msgbuf.body = htonl(getpid()); /* IMPORTANT! */
  msgbuf.tail = '>';
  
  int dest_size = sizeof(dest);
  sendto(socket_fd, &send_message, sizeof(get_message), 0, (struct sockaddr *)&dest, sizeof(dest));//The function retrieves the amount of bits that was send (return -1 in case of a error).
  recvfrom(socket_fd, &get_message, sizeof(get_message), 0, (struct sockaddr *)&dest, (int*) &dest_size);        
  printf("Got data ::%s\n", get_message);
  fflush(stdout);
  return 0;
}

