.PHONY: all clean

CC = gcc
CFLAGS = -g -Wall

all:
	$(CC) $(CFLAGS) -pthread -lzmq hello_world_client.c -o hello_world_client
	$(CC) $(CFLAGS) -pthread -lzmq hello_world_server.c -o hello_world_server
	#$(CC) $(CFLAGS) -pthread -lzmq hwclient.c -o hwclient
	#$(CC) $(CFLAGS) -pthread -lzmq hwserver.c -o hwserver


clean:
	@rm -f *.o
