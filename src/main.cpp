#include "ConsoleReader.cpp"
#include "FileWriter.cpp"
#include "MultiThreadCommandProcessor.cpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    int block_size = std::stoi(argv[1]);
    std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader());
    std::shared_ptr<FileWriter> fileWriter1 = std::make_shared<FileWriter>("bulk1", ".log");
    std::shared_ptr<FileWriter> fileWriter2 = std::make_shared<FileWriter>("bulk2", ".log");
    MultiThreadCommandProcessor commandProcessor = MultiThreadCommandProcessor(block_size, consoleReader, fileWriter1, fileWriter2);
    commandProcessor.process_data();
}