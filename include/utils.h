#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h>
#define MAX_ADDRESS_SIZE 17
#define MAX_PORT_SIZE 6

int createSocketIPv4TCP(int* socketFileDescriptor);

int createAddressIPv4(struct sockaddr_in* socketAddress);

void enterAddressAndPort(char* address, int* port);

#endif //UTILS_H
