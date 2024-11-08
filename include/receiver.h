#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <netinet/in.h>
#define MAX_FILENAME_LENGTH 32

int connectToSender(int socketFileDescriptor, struct sockaddr_in socketAddress);

int receiveFile(int socketFileDescriptor);

int receiveFileName(int socketFileDescriptor, char** fileName);

int receiveFileSize(int socketFileDescriptor, long *fileSize);

int receiveFileData(int socketFileDescriptor, FILE** receivedFile, long fileSize);

int setPathToReceivedFile(char **pathToReceivedFile, const char *fileName);

int setPathToHomeDirectory(char **homeDirectory);

int openFileInBinaryWriteMode(FILE** receivedFile, const char* pathToReceivedFile);

#endif //CLIENT_H