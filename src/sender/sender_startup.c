#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/sender.h"
#include "../../include/utils.h"

int main(int argc, char* argv[]) {
    int socketFileDescriptor;
    if (createSocketIPv4TCP(&socketFileDescriptor)) return EXIT_FAILURE;

    struct sockaddr_in socketAddress;
    if (createAddressIPv4(&socketAddress, "127.0.0.1", 1111)) return EXIT_FAILURE;

    if (bindSocketIPv4(socketFileDescriptor, socketAddress)) return EXIT_FAILURE;

    int connectionSocket;
    acceptConnection(&connectionSocket, socketFileDescriptor, socketAddress);

    if (sendFile(connectionSocket, "./test.jpg")) return EXIT_FAILURE;

    close(connectionSocket);
    close(socketFileDescriptor);

    puts("done");

    return EXIT_SUCCESS;
}
