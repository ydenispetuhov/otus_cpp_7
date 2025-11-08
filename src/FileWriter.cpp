//
// Created by PetukhovDG on 07.11.2025.
//


#include <chrono>
#include <fstream>
#include "writer.h"

class FileWriter : public IWriter {
public:
    FileWriter(std::string filename_prefix, std::string filename_suffix)
            : m_filename_prefix(std::move(filename_prefix)), m_filename_suffix(std::move(filename_suffix)) {}

    void write(const std::string &str) override {
        using namespace std::chrono;
        std::uint64_t time = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
        std::string filename = m_filename_prefix + std::to_string(time) + m_filename_suffix;
        std::ofstream file(filename);
        file << str;
    }

    void write(const std::string &str, std::uint64_t time) {
        std::string filename = m_filename_prefix + std::to_string(time) + m_filename_suffix;
        std::ofstream file(filename);
        file << str;
    }

    virtual ~FileWriter() = default;

private:
    std::string m_filename_prefix;
    std::string m_filename_suffix;
};

