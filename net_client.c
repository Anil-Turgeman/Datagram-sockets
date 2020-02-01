#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10
//#define IP_ADDRESS "217.132.109.191" 
#define PORT 1337 

int main(int argc, char* argv[])
{ 
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 
  struct addrinfo* res;
  struct sockaddr_in* server_addr;
  char* host_name;
  char* host_addr;  

  if(argc != 2){
	perror("Error, please use host name lookup\n");
	exit(1);
  }  
  
  host_name = argv[1];
  int getInfo = getaddrinfo(host_name, NULL, NULL, &res);

  if(getInfo != 0){
	fprintf(stderr, "Error resolving hostname %s\n", host_name);
  	exit(1);
  }

  server_addr = (struct sockaddr_in*)res->ai_addr;
  host_addr = inet_ntoa(server_addr->sin_addr);
  printf("The address of %s is %s\n", host_name, host_addr);

  printf("Client is alive and establishing socket connection.\n");
  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      

  memset((char *)&cli_name,0, sizeof(cli_name)); 
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(host_addr); 
  cli_name.sin_port = htons(PORT);


  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }


  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

} 
