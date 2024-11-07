#ifndef SENDER_H
#define SENDER_H

#include <stdio.h>
#include <netinet/in.h>

int bindSocketIPv4(int socketFileDescriptor, struct sockaddr_in socketAddress);

int acceptConnection(int* clientSocket, int socketFileDescriptor, struct sockaddr_in socketAddress);

int sendFile(int connectionSocket, const char* fileName);

int sendFileSize(int connectionSocket, FILE* fileDescriptor);

int sendFileData(int connectionSocket, FILE* fileDescriptor);

int openFileInBinaryReadMode(FILE** fileDescriptor, const char* fileName);

long getFileSize(FILE* fileDescriptor);

#endif //SENDER_H
