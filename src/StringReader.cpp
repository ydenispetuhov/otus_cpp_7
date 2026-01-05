//
// Created by PetukhovDG on 05.01.2026.
//
#include "../include/reader.h"

#include <string>
#include <sstream>

class StringReader : public IReader {
public:
    StringReader(std::istringstream &&input = std::move(std::istringstream())) : m_input{input} {};

    void add_data(const char * data, std::size_t size) override{
        string_data = std::string(data, data + size);
    };

    bool read(std::string &line) override {
        m_input.str(string_data) ;
        return (bool)std::getline(m_input, line);
    };

    ~StringReader() {};

private:
    void open_brace() {};

    void close_brace() {};

    void notify_end_input() {};

    void notify_new_line(const std::string &line) {};

    std::istringstream &m_input;

    std::string string_data;
};
