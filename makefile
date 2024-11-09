CC = gcc
CFLAGS = -Werror -Wall -g -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SENDER_SOURCE = $(wildcard ${SRCDIR}sender/*.c) \
				$(wildcard ${SRCDIR}other/*.c)
RECEIVER_SOURCE = $(wildcard ${SRCDIR}receiver/*.c) \
				$(wildcard ${SRCDIR}other/*.c)

all: clean sender_compile receiver_compile

sender_compile:
ifeq ($(OS_NAME), Linux)
	$(CC) $(SENDER_SOURCE) $(CFLAGS) -o sender -lpthread
else
	$(CC) $(SENDER_SOURCE) $(CFLAGS) -o sender -lws2_32 -lwsock32
endif

receiver_compile:
ifeq ($(OS_NAME), Linux)
	$(CC) $(RECEIVER_SOURCE) $(CFLAGS) -o receiver -lpthread
else
	$(CC) $(RECEIVER_SOURCE) $(CFLAGS) -o receiver -lws2_32 -lwsock32
endif

clean:
ifeq ($(OS_NAME), Linux)
	rm -f ./sender ./receiver
else
	del /f sender.exe receiver.exe
endif