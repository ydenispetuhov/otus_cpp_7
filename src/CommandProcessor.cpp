//
// Created by PetukhovDG on 07.11.2025.
//

#include <iostream>
#include <queue>
#include <stack>
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
            if (line_ == "{") {
                if (stack.empty()) {
                    while (!queue.empty()) {
                        writer_->write(queue.front());
                        queue.pop();
                    }
                    writer_->write("\n");
                }
                stack.push(line_);
                continue;
            } else if (line_ == "}") {
                stack.pop();
                if (stack.empty()) {
                    while (!queue.empty()) {
                        writer_->write(queue.front());
                        queue.pop();
                    }
                    writer_->write("\n");
                }
                continue;
            } else {
                queue.push(line_);
            }
            if (stack.empty() && queue.size() == c_block_size) {
                while (!queue.empty()) {
                    writer_->write(queue.front());
                    queue.pop();
                }
                writer_->write("\n");
            }
        }
    };

    ~CommandProcessor() = default;

private:
    std::shared_ptr<IWriter> writer_;
    std::shared_ptr<IReader> reader_;
    std::queue<std::string> queue;
    std::stack<std::string> stack;
    int c_block_size;
};


