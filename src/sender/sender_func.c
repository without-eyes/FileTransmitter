#include "../../include/sender.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>

int bindSocketIPv4(const int socketFileDescriptor, struct sockaddr_in socketAddress) {
    const int bindingResult = bind(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (bindingResult == -1) {
        perror("Connection with the client failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int acceptConnection(int* clientSocket, const int socketFileDescriptor, struct sockaddr_in socketAddress) {
    listen(socketFileDescriptor, 1);
    socklen_t socketLength = sizeof(socketAddress);
    *clientSocket = accept(socketFileDescriptor, (struct sockaddr*)&socketAddress, &socketLength);
    if (*clientSocket == -1) {
        perror("Connection with the client failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int sendFile(const int connectionSocket, const char* fileName) {
    FILE* fileDescriptor = fopen(fileName, "rb"); // Open in binary mode
    if (fileDescriptor == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Get file size
    fseek(fileDescriptor, 0, SEEK_END);
    long fileSize = ftell(fileDescriptor);
    fseek(fileDescriptor, 0, SEEK_SET);

    // Send the file size
    write(connectionSocket, &fileSize, sizeof(fileSize));

    // Send the file data in chunks
    char buffer[BUFSIZ];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileDescriptor)) > 0) {
        write(connectionSocket, buffer, bytesRead);
    }

    fclose(fileDescriptor);
    return EXIT_SUCCESS;
}