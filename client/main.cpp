#include "network.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

void printUsage() {
    std::cout << "Usage:\n"
              << "./client read <filename>\n"
              << "./client write <filename>\n"
              << "./client list\n";
}

int main(int argc, char* argv[]) {
    std::cout << "Client running..." << std::endl;
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    if (command == "read" && argc == 3) {
        std::string filename = argv[2];

        // Check if file is already cached
        if (fileCache.find(filename) != fileCache.end()) {
            std::cout << "File contents (from cache):\n" << fileCache[filename] << std::endl;
        } else {
            std::cout << "Fetching file from server...\n";
            sendMessageToServer("127.0.0.1", 8080, "READ " + filename);
        }

    } else if (command == "write" && argc == 3) {
        std::string filename = argv[2];

        // Read the file contents
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Error opening file: " << filename << std::endl;
            return 1;
        }

        std::string fileContents((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

        // Send file contents to the server
        sendMessageToServer("127.0.0.1", 8080, "WRITE " + filename + " " + fileContents);
    } else if (command == "list") {
        sendMessageToServer("127.0.0.1", 8080, "LIST");
    } else {
        printUsage();
    }

    return 0;
}
