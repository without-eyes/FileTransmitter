#include <stdlib.h>
#include "../../include/receiver.h"
#include "../../include/utils.h"

int main() {
#ifdef _WIN32
    if (initializeWinsock()) return EXIT_FAILURE;
#endif

    SOCKET socketFileDescriptor;
    if (createSocketIPv4TCP(&socketFileDescriptor)) return EXIT_FAILURE;

    SOCKADDR_IN socketAddress;
    if (createAddressIPv4(&socketAddress, "127.0.0.1", 1111)) return EXIT_FAILURE;

    if (connectToSender(socketFileDescriptor, socketAddress)) return EXIT_FAILURE;

    if (receiveFile(socketFileDescriptor)) return EXIT_FAILURE;

#ifdef _WIN32
    closesocket(socketFileDescriptor);
    WSACleanup();
#elif unix
    close(socketFileDescriptor);
#endif

    return EXIT_SUCCESS;
}
