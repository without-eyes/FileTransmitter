CC = gcc
CFLAGS = -Werror -Wall -g -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SENDER_SOURCE = $(wildcard ${SRCDIR}sender/*.c) \
				$(wildcard ${SRCDIR}other/*.c)
RECEIVER_SOURCE = $(wildcard ${SRCDIR}receiver/*.c) \
				$(wildcard ${SRCDIR}other/*.c)

all: clean sender receiver

sender: $(SENDER_SOURCE)
	$(CC) $(SENDER_SOURCE) $(CFLAGS) -o $@

receiver: $(RECEIVER_SOURCE)
	$(CC) $(RECEIVER_SOURCE) $(CFLAGS) -o $@

clean:
	rm -f ./sender ./receiver