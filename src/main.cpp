#include "ConsoleReader.cpp"
#include "FileWriter.cpp"
#include "CommandProcessor.cpp"

#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    std::ifstream in("hello.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
    std::ifstream in("hello.txt");
    std::shared_ptr<ConsoleReader> consoleReader = std::make_shared<ConsoleReader>(ConsoleReader(in));
    std::shared_ptr<FileWriter> fileWriter = std::make_shared<FileWriter>(FileWriter("bulk", ".log"));
    CommandProcessor commandProcessor = CommandProcessor(consoleReader, fileWriter);
    commandProcessor.process_data();
    }
    in.close(); 
}