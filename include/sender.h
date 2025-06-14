#ifndef SENDER_H
#define SENDER_H

#include <stdio.h>
#include <netinet/in.h>
#define MAX_FILEPATH_LENGTH 128

int bindSocketIPv4(int socketFileDescriptor, struct sockaddr_in* socketAddress);

int acceptConnection(int* clientSocket, int socketFileDescriptor, struct sockaddr_in socketAddress);

int sendFile(int connectionSocket, char* pathToFile);

int sendFileName(int connectionSocket, char* pathToFile);

int sendFileSize(int connectionSocket, FILE* fileDescriptor);

int sendFileData(int connectionSocket, FILE* fileDescriptor);

int openFileInBinaryReadMode(FILE** fileDescriptor, const char* pathToFile);

long getFileSize(FILE* fileDescriptor);

#endif //SENDER_H
