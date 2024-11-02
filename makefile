CC = gcc
CFLAGS = -Werror -Wall -g

all: clean server_compile client_compile
server: clean server_compile
client: clean client_compile

server_compile:
	$(CC) server.c $(CFLAGS) -o server


client_compile:
	$(CC) client.c $(CFLAGS) -o client

clean:
	rm -f ./client ./server