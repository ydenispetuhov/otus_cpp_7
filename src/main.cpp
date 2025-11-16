#include "ConsoleReader.cpp"
#include "FileWriter.cpp"
#include "CommandProcessor.cpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    int block_size = std::stoi(argv[1]);
    std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader());
    std::shared_ptr<FileWriter> fileWriter = std::make_shared<FileWriter>(FileWriter("bulk", ".log"));
    CommandProcessor commandProcessor = CommandProcessor(block_size, consoleReader, fileWriter);
    commandProcessor.process_data();
}