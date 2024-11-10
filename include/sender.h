#ifndef SENDER_H
#define SENDER_H

#include <stdio.h>
#include "os_directives.h"
#define MAX_FILEPATH_LENGTH 128

int bindSocketIPv4(SOCKET socketFileDescriptor, SOCKADDR_IN socketAddress);

int acceptConnection(SOCKET* clientSocket, SOCKET socketFileDescriptor, SOCKADDR_IN socketAddress);

int sendFile(SOCKET connectionSocket, char* pathToFile);

int sendFileName(SOCKET connectionSocket, char* pathToFile);

int sendFileSize(SOCKET connectionSocket, FILE* fileDescriptor);

int sendFileData(SOCKET connectionSocket, FILE* fileDescriptor);

int openFileInBinaryReadMode(FILE** fileDescriptor, const char* pathToFile);

long getFileSize(FILE* fileDescriptor);

const char* getFilenameFromPath(const char* path);

#endif //SENDER_H
