#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H

#include <string>
#include <unordered_map>

extern std::unordered_map<std::string, std::string> fileCache;

void sendMessageToServer(const std::string& host, int port, const std::string& message);

#endif