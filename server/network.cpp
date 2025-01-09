#include "network.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <filesystem>

const std::string STORAGE_DIR = "storage/";

struct FileMetadata {
    int version;
    std::time_t lastModified;
};

std::unordered_map<std::string, FileMetadata> fileMetadata;

void updateMetadata(const std::string& filename) {
    if (fileMetadata.find(filename) == fileMetadata.end()) {
        // New file, version 1
        fileMetadata[filename] = {1, std::time(nullptr)};
    } else {
        // Update file
        fileMetadata[filename].version += 1;
        fileMetadata[filename].lastModified = std::time(nullptr);
    }
}

void handleClient(int clientSocket) {
    char buffer[1024] = {0};
    read(clientSocket, buffer, sizeof(buffer));
    std::string request(buffer);

    std::istringstream iss(request);
    std::string command, filename, fileData;
    iss >> command >> filename;

    if (command == "READ") {
        std::string filePath = STORAGE_DIR + filename;
        if (std::filesystem::exists(filePath)) {
            std::ifstream file(filePath);
            std::stringstream fileContents;
            fileContents << file.rdbuf();
            std::string response = "OK\n" + fileContents.str();
            send(clientSocket, response.c_str(), response.size(), 0);
        } else {
            std::string error = "ERROR: File not found\n";
            send(clientSocket, error.c_str(), error.size(), 0);
        }
    } else if (command == "WRITE") {
        std::getline(iss, fileData);
        std::string filePath = STORAGE_DIR + filename;

        // Save the file
        std::ofstream outFile(filePath);
        if (outFile.is_open()) {
            outFile << fileData;
            outFile.close();

            // Update metadata
            updateMetadata(filename);

            std::string successMessage = "OK: File written successfully\n";
            send(clientSocket, successMessage.c_str(), successMessage.size(), 0);
        } else {
            std::string error = "ERROR: Failed to write file\n";
            send(clientSocket, error.c_str(), error.size(), 0);
        }

    } else {

        std::string error = "ERROR: Unknown command\n";
        send(clientSocket, error.c_str(), error.size(), 0);
    }

    close(clientSocket);
}

void startServer(const std::string& host, int port) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << "..." << std::endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        std::thread(handleClient, clientSocket).detach();
    }

    close(serverSocket);
}
