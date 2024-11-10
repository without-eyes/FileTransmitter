#ifndef UTILS_H
#define UTILS_H

#include "os_directives.h"

#ifdef _WIN32
#include <stdio.h>

int initializeWinsock(void);
#endif

int createSocketIPv4TCP(SOCKET* socketFileDescriptor);

int createAddressIPv4(SOCKADDR_IN* socketAddress, const char* address, int port);

#endif //UTILS_H
