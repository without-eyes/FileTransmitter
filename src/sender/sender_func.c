#include "../../include/sender.h"

#include <stdlib.h>
#include <fcntl.h>
#include <libgen.h>

int bindSocketIPv4(const SOCKET socketFileDescriptor, SOCKADDR_IN socketAddress) {
    const int bindingResult = bind(socketFileDescriptor, (struct sockaddr*)&socketAddress, sizeof(socketAddress));
    if (bindingResult == -1) {
        perror("Connection with the client failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int acceptConnection(SOCKET* clientSocket, const SOCKET socketFileDescriptor, SOCKADDR_IN socketAddress) {
    listen(socketFileDescriptor, 1);
    socklen_t socketLength = sizeof(socketAddress);
    *clientSocket = accept(socketFileDescriptor, (struct sockaddr*)&socketAddress, &socketLength);
    if (*clientSocket == -1) {
        perror("Accepting connection with the client failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int sendFile(const SOCKET connectionSocket, char* pathToFile) {
    FILE* fileDescriptor = NULL;

    if (openFileInBinaryReadMode(&fileDescriptor, pathToFile) == EXIT_FAILURE) return EXIT_FAILURE;

    if (sendFileName(connectionSocket, pathToFile) == EXIT_FAILURE) return EXIT_FAILURE;

    if (sendFileSize(connectionSocket, fileDescriptor) == EXIT_FAILURE) return EXIT_FAILURE;

    if (sendFileData(connectionSocket, fileDescriptor) == EXIT_FAILURE) return EXIT_FAILURE;

    fclose(fileDescriptor);

    puts("File was successfully sent!");

    return EXIT_SUCCESS;
}

int sendFileName(const SOCKET connectionSocket, char* pathToFile) {
    const char* fileName = getFilenameFromPath(pathToFile);
    size_t fileNameLength = strlen(fileName) + 1;
    if (send(connectionSocket, fileName, fileNameLength, 0) == -1) {
        perror("Error sending file name");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int sendFileSize(const SOCKET connectionSocket, FILE* fileDescriptor) {
    const long fileSize = getFileSize(fileDescriptor);
    if (send(connectionSocket, (const char*)&fileSize, sizeof(fileSize), 0) == -1) {
        perror("Error sending file size");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int sendFileData(const SOCKET connectionSocket, FILE* fileDescriptor) {
    char buffer[BUFSIZ];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileDescriptor)) > 0) {
        size_t bytesSent = 0;

        while (bytesSent < bytesRead) {
            ssize_t result = send(connectionSocket, buffer + bytesSent, bytesRead - bytesSent, 0);
            if (result == -1) {
                int error = WSAGetLastError();
                fprintf(stderr, "Error sending chunk of file data: %d\n", error);
                return EXIT_FAILURE;
            }

            bytesSent += result;
        }
    }

    if (ferror(fileDescriptor)) {
        fprintf(stderr, "Error reading from file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int openFileInBinaryReadMode(FILE** fileDescriptor, const char* pathToFile) {
    *fileDescriptor = fopen(pathToFile, "rb");
    if (*fileDescriptor == NULL) {
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

const char* getFilenameFromPath(const char* path) {
#ifdef _WIN32
    const char* p = path + strlen(path);
    while (p != path) {
        if (*(--p) == '\\' || *p == '/') {
            return p + 1;
        }
    }
    return path;

#elif unix
    return basename(path);
#endif
}