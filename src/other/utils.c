#include "../../include/utils.h"

#include <stdlib.h>

#ifdef _WIN32
int initializeWinsock(void) {
    struct WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData)) {
        int error = WSAGetLastError();
        printf("Error: %d", error);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif

int createSocketIPv4TCP(SOCKET* socketFileDescriptor) {
    *socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (*socketFileDescriptor == -1) {
        perror("Socket creation failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int createAddressIPv4(SOCKADDR_IN * socketAddress, const char* address, const int port) {
    socketAddress->sin_family = AF_INET;
    socketAddress->sin_addr.s_addr = inet_addr(address);
    socketAddress->sin_port = htons(port);
    return EXIT_SUCCESS;
}