#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <chrono>

struct FileMetadata {
    size_t size;
    int version;
    std::string filename;
    std::chrono::system_clock::time_point last_modified;

    FileMetadata(std::string fname, size_t fsize, int ver)
        : filename(fname), size(fsize), version(ver),
          last_modified(std::chrono::system_clock::now()) {}

    std::string getFormattedTime() const {
        auto time = std::chrono::system_clock::to_time_t(last_modified);
        return std::ctime(&time);
    }
};

#endif
