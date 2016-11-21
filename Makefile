CC=gcc

all: client server

server: server.c
	$(CC) -o server server.c

client : client.o funcs.o
	$(CC) -o client client.o funcs.o 

client.o : client.c
	$(CC) -c client.c

funcs.o: funcs.c funcs.h
	$(CC) -c funcs.c

Clean: 
	rm -f *.o client server
