#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include "os_directives.h"
#define MAX_FILENAME_LENGTH 32

int connectToSender(SOCKET socketFileDescriptor, SOCKADDR_IN socketAddress);

int receiveFile(SOCKET socketFileDescriptor);

int receiveFileName(SOCKET socketFileDescriptor, char** fileName);

int receiveFileSize(SOCKET socketFileDescriptor, long *fileSize);

int receiveFileData(SOCKET socketFileDescriptor, FILE** receivedFile, long fileSize);

int setPathToReceivedFile(char **pathToReceivedFile, const char *fileName);

int setPathToHomeDirectory(char **homeDirectory);

int openFileInBinaryWriteMode(FILE** receivedFile, const char* pathToReceivedFile);

#endif //CLIENT_H