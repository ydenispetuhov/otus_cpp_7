//
// Created by PetukhovDG on 07.11.2025.
//

#include <iostream>
#include "processor.h"
#include "reader.h"

class CommandProcessor : public IProcessor {
public:
    CommandProcessor(std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer) : reader_{reader},
                                                                                         writer_{writer} {}

    void process_data() override {
        std::string line_;
        while (reader_->read(line_)) {
            writer_->write(line_);
        }
    };

    ~CommandProcessor() = default;

private:
    std::shared_ptr<IWriter> writer_;
    std::shared_ptr<IReader> reader_;
};


