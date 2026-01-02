#include "ConsoleReader.cpp"
#include "FileWriter.cpp"
#include "MultiThreadCommandProcessor.cpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    std::ifstream in("../bulk_origin.txt");
    std::ofstream of1(
        "bulk1" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count()) + ".log", std::ios::app);
    std::ofstream of2(
        "bulk2" + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count()) + ".log", std::ios::app);
    if (in.is_open()) {
        int block_size = 3;//std::stoi(argv[1]);
        MultiThreadCommandProcessor commandProcessor(block_size,
                                                     std::make_shared<ConsoleReader>(in),
                                                     std::make_shared<FileWriter>(of1),
                                                     std::make_shared<FileWriter>(of2));
        commandProcessor.process_data();
    }
    in.close();

    // int block_size = std::stoi(argv[1]);
    // std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader());
    // std::shared_ptr<FileWriter> fileWriter1 = std::make_shared<FileWriter>(FileWriter("bulk1", ".log"));
    // std::shared_ptr<FileWriter> fileWriter2 = std::make_shared<FileWriter>(FileWriter("bulk2", ".log"));
    // MultiThreadCommandProcessor commandProcessor = MultiThreadCommandProcessor(block_size, consoleReader, fileWriter1, fileWriter2);
    // commandProcessor.process_data();
}