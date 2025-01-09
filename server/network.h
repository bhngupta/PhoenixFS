#ifndef SERVER_NETWORK_H
#define SERVER_NETWORK_H

#include <string>

void startServer(const std::string& host, int port);
void handleClient(int clientSocket);

#endif
