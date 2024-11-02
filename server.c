#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
    const int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in* address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(1111);
    address->sin_addr.s_addr = inet_addr("127.0.0.1");

    const int result = bind(socketFileDescriptor, (struct sockaddr*)address, sizeof(*address));
    if (result == -1) {
        perror("Connection with the client failed");
        return -1;
    }

    listen(socketFileDescriptor, 1);
    socklen_t socketLength = sizeof(address);
    const int clientSocket = accept(socketFileDescriptor, (struct sockaddr*)address, &socketLength);

    free(address);
    return 0;
}
