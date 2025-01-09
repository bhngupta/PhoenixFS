#include "network.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Define the file cache
std::unordered_map<std::string, std::string> fileCache;

void cacheFile(const std::string& filename, const std::string& contents) {
    fileCache[filename] = contents;

    std::ofstream localFile(filename);
    localFile << contents;
    localFile.close();

    std::cout << "File cached: " << filename << std::endl;
}

void sendMessageToServer(const std::string& host, int port, const std::string& message) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        return;
    }

    sockaddr_in serverAddress = {};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serverAddress.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        return;
    }

    send(clientSocket, message.c_str(), message.size(), 0);

    char buffer[4096] = {0};
    read(clientSocket, buffer, sizeof(buffer));
    std::string response(buffer);

    if (response.find("OK") == 0) {
        std::string contents = response.substr(3); // Skip "OK\n"
        std::cout << "File contents:\n" << contents << std::endl;

        // Cache the file
        if (message.find("READ") == 0) {
            std::istringstream iss(message);
            std::string command, filename;
            iss >> command >> filename;
            fileCache[filename] = contents;

            cacheFile(filename, contents);
        }
    } else {
        std::cout << response << std::endl; // Print error message
    }

    close(clientSocket);
}
