#include "../../include/receiver.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int connectToSender(const int socketFileDescriptor, const struct sockaddr_in socketAddress) {
    const int connectionResult = connect(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (connectionResult == -1) {
        perror("Connection with the server failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFile() {
    return EXIT_SUCCESS;
}