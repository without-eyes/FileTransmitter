#ifndef SENDER_H
#define SENDER_H

int bindSocketIPv4(int socketFileDescriptor, struct sockaddr_in socketAddress);

int acceptConnection(int* clientSocket, int socketFileDescriptor, struct sockaddr_in socketAddress);

#endif //SENDER_H
