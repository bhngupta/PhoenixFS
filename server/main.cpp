#include "network.h"
#include <iostream>

int main() {
  std::cout << "Server running..." << std::endl;

  startServer("127.0.0.1", 8080);

  return 0;
}
