//
// Created by PetukhovDG on 07.11.2025.
//

#include <chrono>
#include <fstream>
#include "writer.h"

class FileWriter : public IWriter {
public:
    explicit FileWriter(std::ofstream& file_) : m_file(file_) {}
//    explicit FileWriter(const std::string filename_prefix, const std::string filename_suffix) : m_file(std::ofstream(
//                    filename_prefix + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(
//                            std::chrono::high_resolution_clock::now().time_since_epoch()).count()) + filename_suffix, std::ios::app)) {}

    FileWriter(FileWriter &&fileWriter) : m_file(fileWriter.getFileStream()) {}


    FileWriter(FileWriter &fileWriter) : m_file(fileWriter.getFileStream()) {}

    void write(const std::string &str) override {
        m_file << str;
    }

    void write(const std::string &str, std::uint64_t time) {
        m_file << str;
    }

    std::ofstream &getFileStream() {
        return m_file;
    }

    virtual ~FileWriter() = default;

private:
    std::ofstream& m_file;
};

