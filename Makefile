# Makefile for ex4 Part A

all: recv_udp send_udp

recv_udp: recv_udp.c
	gcc -Werror -Wall -Wvla -g recv_udp.c -o recv_udp.o

send_udp: send_udp.c
	gcc -Werror -Wall -Wvla -g send_udp.c -o send_udp.o

clean:
	rm -f *.o recv_udp.o send_udp.o

runs:
	./recv_udp.o

runc:
	./send_udp.o localhost

runs-strace:
	strace -f ./recv_udp.o

runc-strace:
	strace -f ./send_udp.o
