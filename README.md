# PhoenixFS

PheonixFS is a lightweight, multithreaded distributed file system designed for read and write operations across multiple servers. It simulates a real-world distributed storage system, providing efficient file access and replication capabilities, akin to modern systems used in cloud computing and large-scale data centers.

## Features

- Distributed Architecture: Supports primary-secondary replication for high availability and fault tolerance.
- Read and Write Operations: Efficiently handles file read and write requests with caching mechanisms for faster access.
- Caching: Implements an in-memory client-side cache for frequently accessed files.
- Replication: Ensures data consistency across multiple servers with a simple replication protocol.
- Concurrency: Utilizes multithreading to handle simultaneous client requests and server-side replication.
- Metadata Management: Stores and updates file metadata, including versioning and timestamps, ensuring accurate file tracking.


## Choice of Language

- C++ was chosen for this project due to its:

- High Performance: Optimal for systems requiring low latency and high throughput.
- Memory Control: Provides fine-grained control over memory management, crucial for system-level programming.
- Concurrency Support: Offers robust multithreading capabilities to handle concurrent operations.

## Components of DFS

The system consists of two main components:

1. Primary Server: Handles all client requests, processes read and write operations, and forwards write updates to secondary servers.
2. Secondary Servers: Receive and apply updates from the primary server, ensuring data consistency across the system.

## Getting Started

### Prerequisites

Ensure you have the following installed:

- Git: Version control system
- C++ Compiler: For compiling C++ code
- CMake: Build tool

### Installation

1. Clone the repository:

```bash
git clone https://github.com/bhngupta/PhoenixFS
cd PhoenixFS
```

2. Build the project:

```bash
mkdir build && cd build
cmake ..
make
```

### Running the Servers

1. Start the Primary Server

```bash
./primary_server
```

2. Start Secondary Servers (in separate terminals):

```bash
./secondary_server 8081
./secondary_server 8082
```

### Running the Client

1. Write a file:

```bash
./client write test.txt
```

2. Read a file:

```bash
./client read test.txt
```

3. List all files:

```bash
./client list
```

## Usage
The system supports basic CLI commands for interacting with the distributed file system:

- Read a file: Retrieve file content from the server.
- Write a file: Upload file content to the server, with replication to secondary servers.
- List all files: Lists all files in the file system

## Future Plans

- [ ] Persistence: Add support for persistent storage using databases like SQLite.
- [ ] Enhanced Replication: Introduce more sophisticated replication protocols for improved consistency and fault tolerance.
- [ ] Caching: Implement more sophisticated caching strategies for better performance.
- [ ] Web Interface: Develop a web-based interface for monitoring and managing Phoenix file system.

## License

This project is licensed under the [MIT License](https://opensource.org/license/MIT) - see the [LICENSE](https://github.com/bhngupta/PhoenixFS/blob/main/LICENSE) file for details.
