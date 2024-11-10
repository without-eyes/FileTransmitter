#include <stdio.h>
#include <stdlib.h>

#include "../../include/sender.h"
#include "../../include/utils.h"

int main() {
#ifdef _WIN32
    if (initializeWinsock()) return EXIT_FAILURE;
#endif

    SOCKET socketFileDescriptor;
    if (createSocketIPv4TCP(&socketFileDescriptor)) return EXIT_FAILURE;

    SOCKADDR_IN socketAddress;
    if (createAddressIPv4(&socketAddress, "127.0.0.1", 1111)) return EXIT_FAILURE;

    if (bindSocketIPv4(socketFileDescriptor, socketAddress)) return EXIT_FAILURE;

    SOCKET connectionSocket;
    acceptConnection(&connectionSocket, socketFileDescriptor, socketAddress);

    char pathToFile[MAX_FILEPATH_LENGTH];
    printf("Enter path to file you want to send: ");
#ifdef _WIN32
    fgets(pathToFile, sizeof(pathToFile), stdin);
    const size_t length = strlen(pathToFile);
    if (length > 0 && pathToFile[length - 1] == '\n') {
        pathToFile[length - 1] = '\0';
    }
#elif unix
    scanf("%s", pathToFile);
#endif

    if (sendFile(connectionSocket, pathToFile)) return EXIT_FAILURE;

#ifdef _WIN32
    shutdown(connectionSocket, SD_SEND);
    closesocket(connectionSocket);
    closesocket(socketFileDescriptor);
    WSACleanup();
#elif unix
    close(connectionSocket);
    close(socketFileDescriptor);
#endif

    return EXIT_SUCCESS;
}
