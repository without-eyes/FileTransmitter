#include "../../include/sender.h"

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
    FILE* fileDescriptor = NULL;

    if (openFileInBinaryReadMode(fileDescriptor, fileName) == EXIT_FAILURE) return EXIT_FAILURE;

    if (sendFileSize(connectionSocket, fileDescriptor) == EXIT_FAILURE) return EXIT_FAILURE;

    if (sendFileData(connectionSocket, fileDescriptor) == EXIT_FAILURE) return EXIT_FAILURE;

    fclose(fileDescriptor);
    return EXIT_SUCCESS;
}

int sendFileSize(const int connectionSocket, FILE* fileDescriptor) {
    const long fileSize = getFileSize(fileDescriptor);
    if (write(connectionSocket, &fileSize, sizeof(fileSize)) == -1) {
        perror("Error sending file size");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int sendFileData(const int connectionSocket, FILE* fileDescriptor) {
    char buffer[BUFSIZ];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileDescriptor)) > 0) {
        if (write(connectionSocket, buffer, bytesRead) == -1) {
            perror("Error sending chunk of file data");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int openFileInBinaryReadMode(const FILE* fileDescriptor, const char* fileName) {
    fileDescriptor = fopen(fileName, "rb");
    if (fileDescriptor == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

long getFileSize(FILE* fileDescriptor) {
    fseek(fileDescriptor, 0, SEEK_END);
    const long fileSize = ftell(fileDescriptor);
    fseek(fileDescriptor, 0, SEEK_SET);
    return fileSize;
}