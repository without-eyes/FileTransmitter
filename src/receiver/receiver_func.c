#include "../../include/receiver.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int connectToSender(int socketFileDescriptor, struct sockaddr_in* socketAddress) {
    const int connectionResult = connect(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(*socketAddress));
    if (connectionResult == -1) {
        perror("Connection with the server failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFile(int socketFileDescriptor) {
    char* fileName;
    if (receiveFileName(socketFileDescriptor, &fileName) != EXIT_SUCCESS) return EXIT_FAILURE;

    char* pathToReceivedFile;
    if (setPathToReceivedFile(&pathToReceivedFile, fileName) == EXIT_FAILURE) return EXIT_FAILURE;

    long fileSize;
    if (receiveFileSize(socketFileDescriptor, &fileSize) == EXIT_FAILURE) return EXIT_FAILURE;

    FILE *receivedFile;
    if (openFileInBinaryWriteMode(&receivedFile, pathToReceivedFile) == EXIT_FAILURE) return EXIT_FAILURE;

    if (receiveFileData(socketFileDescriptor, &receivedFile, fileSize) == EXIT_FAILURE) return EXIT_FAILURE;

    printf("File received successfully: %s\n", pathToReceivedFile);
    fclose(receivedFile);
    free(pathToReceivedFile);
    free(fileName);

    return EXIT_SUCCESS;
}

int receiveFileName(int socketFileDescriptor, char** fileName) {
    *fileName = (char*)malloc(MAX_FILENAME_LENGTH * sizeof(char));
    if (recv(socketFileDescriptor, *fileName, MAX_FILENAME_LENGTH, 0) == -1) {
        perror("Error receiving file name");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFileSize(int socketFileDescriptor, long *fileSize) {
    if (read(socketFileDescriptor, &fileSize, sizeof(*fileSize)) != sizeof(*fileSize)) {
        perror("Error receiving file size");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFileData(int socketFileDescriptor, FILE** receivedFile, const long fileSize) {
    char buffer[BUFSIZ];
    ssize_t bytesReceived;
    long remainingData = fileSize;

    while (remainingData > 0 && (bytesReceived = read(socketFileDescriptor, buffer, sizeof(buffer))) > 0) {
        const size_t bytesWritten = fwrite(buffer, 1, bytesReceived, *receivedFile);
        if (bytesWritten != bytesReceived) {
            perror("Error writing data to file");
            return EXIT_FAILURE;
        }
        remainingData -= bytesReceived;
    }

    return EXIT_SUCCESS;
}

int setPathToReceivedFile(char **pathToReceivedFile, const char *fileName) {
    char* homeDirectory;
    if (setPathToHomeDirectory(&homeDirectory) == EXIT_FAILURE) return EXIT_FAILURE;

    const size_t pathToReceivedFileSize = strlen(homeDirectory) + strlen(fileName) + 12;
    *pathToReceivedFile = (char*)malloc(pathToReceivedFileSize * sizeof(char));
    snprintf(*pathToReceivedFile, pathToReceivedFileSize, "%s/Downloads/%s", homeDirectory, fileName);

    return EXIT_SUCCESS;
}

int setPathToHomeDirectory(char **homeDirectory) {
    *homeDirectory = getenv("HOME");
    if (*homeDirectory == NULL) {
        fprintf(stderr, "Failed to get HOME environment variable.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int openFileInBinaryWriteMode(FILE** receivedFile, const char* pathToReceivedFile) {
    *receivedFile = fopen(pathToReceivedFile, "wb");
    if (*receivedFile == NULL) {
        perror("Error creating file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}