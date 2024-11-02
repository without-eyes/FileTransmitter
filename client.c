#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
    const int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        puts("Socket creation failed");
        return -1;
    }

    struct sockaddr_in* address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(1111);
    address->sin_addr.s_addr = inet_addr("127.0.0.1");

    const int result = connect(socketFileDescriptor, (struct sockaddr*)address, sizeof(*address));
    if (result == -1) {
        puts("Connection with the server failed");
        return -1;
    }

    free(address);
    return 0;
}
