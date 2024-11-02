#include <stdio.h>
#include <stdlib.h>
#include "../../include/receiver.h"
#include "../../include/utils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) return EXIT_FAILURE;

    int socketFileDescriptor;
    if (createSocketIPv4TCP(&socketFileDescriptor)) return EXIT_FAILURE;

    struct sockaddr_in socketAddress;
    if (createAddressIPv4(&socketAddress, argv[1], strtol(argv[2], NULL, 10))) return EXIT_FAILURE;

    if (connectToSender(socketFileDescriptor, socketAddress)) return EXIT_FAILURE;

    if (receiveFile()) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
