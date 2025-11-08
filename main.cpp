#include "src/ConsoleReader.cpp"
#include "src/FileWriter.cpp"
#include "src/CommandProcessor.cpp"

#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader(std::cin));
    std::shared_ptr<FileWriter> fileWriter = std::make_shared<FileWriter>(FileWriter("bulk", ".log"));
    IProcessor commandProcessor = CommandProcessor(consoleReader, fileWriter);
    commandProcessor.process_data();
}