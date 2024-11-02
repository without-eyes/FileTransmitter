#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>

int createSocketIPv4TCP(int* socketFileDescriptor) {
    *socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketFileDescriptor == -1) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int createAddressIPv4(struct sockaddr_in* socketAddress, const char* address, const int port) {
    socketAddress->sin_family = AF_INET;
    socketAddress->sin_addr.s_addr = inet_addr(address);
    socketAddress->sin_port = htons(port);
    return EXIT_SUCCESS;
}