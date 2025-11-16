#include "ConsoleReader.cpp"
#include "FileWriter.cpp"
#include "CommandProcessor.cpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    // std::ifstream in("../bulk_origin.txt");
    std::ofstream of(
            "bulk" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()).count()) + ".log", std::ios::app);
    int block_size = std::stoi(argv[1]);
    // if (in.is_open()) {
        // std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader(in));
        std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader());
        std::shared_ptr<FileWriter> fileWriter = std::make_shared<FileWriter>(FileWriter(of));
        CommandProcessor commandProcessor = CommandProcessor(block_size, consoleReader, fileWriter);
        commandProcessor.process_data();
    // }
    // in.close();
}