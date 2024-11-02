#include "../../include/receiver.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int connectToSender(const int socketFileDescriptor, const struct sockaddr_in socketAddress) {
    const int result = connect(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (result == -1) {
        perror("Connection with the server failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFile() {
    return EXIT_SUCCESS;
}