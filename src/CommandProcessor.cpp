//
// Created by PetukhovDG on 07.11.2025.
//

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <cctype>
#include <locale>
#include "processor.h"
#include "reader.h"

class CommandProcessor : public IProcessor {
public:
    CommandProcessor(int block_size, std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer) :    c_block_size{block_size},
                                                                                                            reader_{reader},
                                                                                                            writer_{writer} {}

    void process_data() override {
        std::string line_;
        while (reader_->read(line_)) {
            ltrim(line_);
            if (line_ == "{") {
                if (stack.empty() && !queue.empty()) {
                    prepare_command_and_write(queue, writer_);
                }
                stack.push(line_);
                continue;
            } else if (line_ == "}") {
                stack.pop();
                if (stack.empty()) {
                    prepare_command_and_write(queue, writer_);
                }
                continue;
            } else {
                queue.push(line_);
            }
            if (stack.empty() && queue.size() == c_block_size) {
                prepare_command_and_write(queue, writer_);
            }
        }
    };

    ~CommandProcessor() = default;

private:

    void prepare_command_and_write(std::queue<std::string>& queue, std::shared_ptr<IWriter>& writer) {
        // std::string result = std::reduce(queue.begin(), queue.end(), " ");
        // result += "\n";
        // writer_->write(result);
        std::string result;
        while (!queue.empty()) {
                    result += queue.front();
                    result += " ";
                    queue.pop();
                }
                result += "\n";
                writer_->write(result);
    }

    // Trim from the start (in place)
    static void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // Trim from the end (in place)
    static void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    std::shared_ptr<IWriter> writer_;
    std::shared_ptr<IReader> reader_;
    std::queue<std::string> queue;
    std::stack<std::string> stack;
    int c_block_size;
};


