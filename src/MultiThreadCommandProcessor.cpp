//
// Created by PetukhovDG on 01.01.2026.
//

#include <queue>
#include <stack>
#include "processor.h"
#include "reader.h"
#include "ThreadPool.h"

class MultiThreadCommandProcessor : public IProcessor {
public:
    MultiThreadCommandProcessor(const int block_size, const std::shared_ptr<IReader> &reader,
                                const std::shared_ptr<IWriter> &writer1,
                                const std::shared_ptr<IWriter> &writer2) : writer_1{writer1},
                                                                          writer_2{writer2},
                                                                          reader_{reader},
                                                                          c_block_size{block_size},
                                                                          pool{std::move(ThreadPool(4))} {
    }

    void process_data() override {
        std::string line_;
        std::string tmp_line_;
        std::shared_ptr<IWriter> currWriter = writer_1;
        while (reader_->read(line_)) {
            if (line_ == "{") {
                if (stack.empty()) {
                    while (!queue.empty()) {
                        tmp_line_.append(queue.front());
                        queue.pop();
                    }
                    tmp_line_.append("\n");
                    // writer_->write(tmp_line_);
                    pool.enqueue([currWriter, tmp_line_]() {currWriter->write(tmp_line_);});
                }
                stack.push(line_);
                continue;
            } else if (line_ == "}") {
                stack.pop();
                if (stack.empty()) {
                    while (!queue.empty()) {
                        tmp_line_.append(queue.front());
                        queue.pop();
                    }
                    tmp_line_.append("\n");
                    // writer_->write(tmp_line_);
                    pool.enqueue([currWriter, tmp_line_]() {currWriter->write(tmp_line_);});
                }
                continue;
            } else {
                queue.push(line_);
            }
            if (stack.empty() && queue.size() == c_block_size) {
                while (!queue.empty()) {
                    tmp_line_.append(queue.front());
                    queue.pop();
                }
                tmp_line_.append("\n");
                // writer_->write(tmp_line_);
                pool.enqueue([currWriter, tmp_line_]() {currWriter->write(tmp_line_);});
            }
        }
    };

    ~MultiThreadCommandProcessor() = default;

private:
    std::shared_ptr<IWriter> writer_1;
    std::shared_ptr<IWriter> writer_2;
    std::shared_ptr<IReader> reader_;
    std::queue<std::string> queue;
    std::stack<std::string> stack;
    int c_block_size;
    ThreadPool&& pool;
};


