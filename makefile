CC = gcc
CFLAGS = -Werror -Wall -g -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SENDER_SOURCE = $(wildcard ${SRCDIR}sender/*.c) \
				$(wildcard ${SRCDIR}other/*.c)
RECEIVER_SOURCE = $(wildcard ${SRCDIR}receiver/*.c) \
				$(wildcard ${SRCDIR}other/*.c)

all: clean sender_compile receiver_compile
sender: clean sender_compile
receiver: clean receiver_compile

sender_compile:
	$(CC) $(SENDER_SOURCE) $(CFLAGS) -o sender

receiver_compile:
	$(CC) $(RECEIVER_SOURCE) $(CFLAGS) -o receiver

clean:
	rm -f ./sender ./receiver