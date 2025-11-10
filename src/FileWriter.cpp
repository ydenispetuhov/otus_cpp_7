//
// Created by PetukhovDG on 07.11.2025.
//

#include <chrono>
#include <fstream>
#include "writer.h"

class FileWriter : public IWriter {
public:
    explicit FileWriter(std::string filename_prefix, std::string filename_suffix) : m_file(m_file = std::ofstream (filename_prefix + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()) + filename_suffix)) {
                // std::uint64_t time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
                // m_file = std::ofstream (filename_prefix + std::to_string(time) + filename_suffix);
            }

    FileWriter(FileWriter&& fileWriter) : m_file(fileWriter.getFileStream()) { }

            

    FileWriter(FileWriter& fileWriter) : m_file(fileWriter.getFileStream()) { }

    void write(const std::string &str) override {
        using namespace std::chrono;
        // std::uint64_t time = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
        // std::string filename = m_filename_prefix + std::to_string(time) + m_filename_suffix;
        // std::ofstream file(filename);
        // file << str;
    }

    void write(const std::string &str, std::uint64_t time) {
        // std::string filename = m_filename_prefix + std::to_string(time) + m_filename_suffix;
        // std::ofstream file(filename);
        // file << str;
        m_file << str;
    }

    std::ofstream& getFileStream(){
        return m_file;
    }

    virtual ~FileWriter() = default;

private:
    // std::string m_filename_prefix;
    // std::string m_filename_suffix;
    std::ofstream& m_file;
};

