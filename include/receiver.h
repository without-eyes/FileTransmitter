#ifndef CLIENT_H
#define CLIENT_H

int connectToSender(int socketFileDescriptor, struct sockaddr_in socketAddress);

int receiveFile();

#endif //CLIENT_H