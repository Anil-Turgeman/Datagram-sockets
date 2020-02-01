# Makefile for ex4 Part B

all: net_client net_server

net_client: net_client.c
	gcc -Werror -Wall -Wvla -g net_client.c -o net_client.o

net_server: net_server.c
	gcc -Werror -Wall -Wvla -g net_server.c -o net_server.o

nslookup: nslookup.c
	gcc -Werror -Wall -Wvla -g nslookup.c -o nslookup.o

clean:
	rm -f *.o net_client.o net_server.o

runserver:
	./net_server.o

runclient:
	./net_client.o

