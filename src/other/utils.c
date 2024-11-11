#include "../../include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int createSocketIPv4TCP(int* socketFileDescriptor) {
    *socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketFileDescriptor == -1) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int createAddressIPv4(struct sockaddr_in* socketAddress) {
    char address[MAX_ADDRESS_SIZE];
    int port;
    enterAddressAndPort(address, &port);

    socketAddress->sin_family = AF_INET;
    socketAddress->sin_addr.s_addr = inet_addr(address);
    socketAddress->sin_port = htons(port);
    return EXIT_SUCCESS;
}

void enterAddressAndPort(char* address, int* port) {
    printf("Enter address: ");
    fgets(address, MAX_ADDRESS_SIZE, stdin);
    address[strlen(address) - 1] = '\0';

    printf("Enter port: ");
    char *ptr;
    char buffer[MAX_PORT_SIZE];
    fgets(buffer, sizeof(buffer), stdin);
    size_t portLength = strlen(buffer);
    if (portLength > 0 && buffer[portLength - 1] == '\n') {
        buffer[portLength - 1] = '\0';
    }
    *port = strtol(buffer, &ptr, 10);
}