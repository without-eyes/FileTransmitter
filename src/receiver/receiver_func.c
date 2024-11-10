#include "../../include/receiver.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int connectToSender(const SOCKET socketFileDescriptor, const struct sockaddr_in socketAddress) {
    const int connectionResult = connect(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (connectionResult == -1) {
        perror("Connection with the server failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFile(const SOCKET socketFileDescriptor) {
    char* fileName;
    if (receiveFileName(socketFileDescriptor, &fileName) != EXIT_SUCCESS) return EXIT_FAILURE;

    char* pathToReceivedFile;
    if (setPathToReceivedFile(&pathToReceivedFile, fileName) == EXIT_FAILURE) return EXIT_FAILURE;
    puts(pathToReceivedFile);

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

int receiveFileName(const SOCKET socketFileDescriptor, char** fileName) {
    *fileName = (char*)malloc(MAX_FILENAME_LENGTH * sizeof(char));
    if (recv(socketFileDescriptor, *fileName, MAX_FILENAME_LENGTH, 0) == -1) {
        perror("Error receiving file name");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFileSize(const SOCKET socketFileDescriptor, long *fileSize) {
    if (recv(socketFileDescriptor, (char *)fileSize, sizeof(*fileSize), 0) != sizeof(*fileSize)) {
        perror("Error receiving file size");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int receiveFileData(const SOCKET socketFileDescriptor, FILE** receivedFile, const long fileSize) {
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
#ifdef _WIN32
    char* environmentVariable = "USERPROFILE";
#elif unix
    char* environmentVariable = "HOME";
#endif

    *homeDirectory = getenv(environmentVariable);
    if (*homeDirectory == NULL) {
        fprintf(stderr, "Failed to get %s environment variable.\n", environmentVariable);
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