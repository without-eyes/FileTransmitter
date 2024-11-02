#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h>

struct File {
    char *filename;
    int *data;
    int size;
};

int createSocketIPv4TCP(int* socketFileDescriptor);

int createAddressIPv4(struct sockaddr_in* socketAddress, const char* address, int port);

#endif //UTILS_H
