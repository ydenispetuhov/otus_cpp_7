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
    MultiThreadCommandProcessor(const int block_size, std::shared_ptr<IReader> reader,
                                std::shared_ptr<IWriter> writer1,
                                std::shared_ptr<IWriter> writer2) 
        : c_block_size{block_size},
          reader_{std::move(reader)},
          writer_1{std::move(writer1)},
          writer_2{std::move(writer2)},
          pool{ThreadPool(4)} {}

    void process_data() override {
        std::string line;
        std::shared_ptr<IWriter> current_writer = writer_1;

        while (reader_->read(line)) {
            if (line == "{") {
                if (stack.empty()) {
                    flush_queue(current_writer);
                }
                stack.push(line);
            } else if (line == "}") {
                stack.pop();
                if (stack.empty()) {
                    flush_queue(current_writer);
                    // Toggle writer after each complete block
                    current_writer = (current_writer == writer_1) ? writer_2 : writer_1;
                }
            } else {
                queue.push(line);
            }

            if (stack.empty() && static_cast<int>(queue.size()) >= c_block_size) {
                flush_queue(current_writer);
                // Toggle writer after each complete block
                current_writer = (current_writer == writer_1) ? writer_2 : writer_1;
            }
        }
    }

    ~MultiThreadCommandProcessor() = default;

private:
    void flush_queue(std::shared_ptr<IWriter>& writer) {
        if (queue.empty()) return;

        std::string block;
        while (!queue.empty()) {
            block += queue.front();
            queue.pop();
        }
        block += "\n";

        pool.enqueue([writer, block]() {
            writer->write(block);
        });
    }

    std::shared_ptr<IWriter> writer_1;
    std::shared_ptr<IWriter> writer_2;
    std::shared_ptr<IReader> reader_;
    std::queue<std::string> queue;
    std::stack<std::string> stack;
    int c_block_size;
    ThreadPool pool;
};