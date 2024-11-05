#include "../../include/receiver.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int connectToSender(const int socketFileDescriptor, const struct sockaddr_in socketAddress) {
    const int connectionResult = connect(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (connectionResult == -1) {
        perror("Connection with the server failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFile(const int socketFileDescriptor) {
    const char *home = getenv("HOME");
    if (home == NULL) {
        fprintf(stderr, "Failed to get HOME environment variable.\n");
        return EXIT_FAILURE;
    }

    char filePath[1024];
    snprintf(filePath, sizeof(filePath), "%s/Downloads/test.jpg", home);
    printf("Downloading file: %s\n", filePath);

    // Receive the file size
    long fileSize;
    read(socketFileDescriptor, &fileSize, sizeof(fileSize));

    // Open file in binary mode
    FILE *receivedFile = fopen(filePath, "wb");
    if (receivedFile == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }

    // Receive the file data in chunks
    char buffer[BUFSIZ];
    ssize_t bytesReceived;
    long remainingData = fileSize;

    while (remainingData > 0 && (bytesReceived = read(socketFileDescriptor, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytesReceived, receivedFile);
        remainingData -= bytesReceived;
    }

    fclose(receivedFile);
    printf("File received successfully\n");

    return EXIT_SUCCESS;
}