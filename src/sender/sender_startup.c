#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/sender.h"
#include "../../include/utils.h"

int main() {
    int socketFileDescriptor;
    if (createSocketIPv4TCP(&socketFileDescriptor)) return EXIT_FAILURE;

    struct sockaddr_in socketAddress;
    if (createAddressIPv4(&socketAddress, "127.0.0.1", 1111)) return EXIT_FAILURE;

    if (bindSocketIPv4(socketFileDescriptor, socketAddress)) return EXIT_FAILURE;

    int connectionSocket;
    acceptConnection(&connectionSocket, socketFileDescriptor, socketAddress);

    char pathToFile[MAX_FILEPATH_LENGTH];
    printf("Enter path to file you want to send: ");
    scanf("%s", pathToFile);

    if (sendFile(connectionSocket, pathToFile)) return EXIT_FAILURE;

    close(connectionSocket);
    close(socketFileDescriptor);

    return EXIT_SUCCESS;
}
