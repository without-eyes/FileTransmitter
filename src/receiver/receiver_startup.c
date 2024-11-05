#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/receiver.h"
#include "../../include/utils.h"

int main(int argc, char* argv[]) {
    int socketFileDescriptor;
    if (createSocketIPv4TCP(&socketFileDescriptor)) return EXIT_FAILURE;

    struct sockaddr_in socketAddress;
    if (createAddressIPv4(&socketAddress, "127.0.0.1", 1111)) return EXIT_FAILURE;

    if (connectToSender(socketFileDescriptor, socketAddress)) return EXIT_FAILURE;

    if (receiveFile(socketFileDescriptor)) return EXIT_FAILURE;

    close(socketFileDescriptor);

    return EXIT_SUCCESS;
}
