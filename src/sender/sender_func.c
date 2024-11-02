#include "../../include/sender.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>

int bindSocketIPv4(const int socketFileDescriptor, struct sockaddr_in socketAddress) {
    const int bindingResult = bind(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (bindingResult == -1) {
        perror("Connection with the client failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int acceptConnection(int* clientSocket, const int socketFileDescriptor, struct sockaddr_in socketAddress) {
    listen(socketFileDescriptor, 1);
    socklen_t socketLength = sizeof(socketAddress);
    *clientSocket = accept(socketFileDescriptor, (struct sockaddr*)&socketAddress, &socketLength);
    if (*clientSocket == -1) {
        perror("Connection with the client failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}