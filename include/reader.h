//
// Created by PetukhovDG on 07.11.2025.
//

#ifndef OTUS_CPP_7_READER_H
#define OTUS_CPP_7_READER_H
#include "storage.h"

#include <memory>

class IReader
{
public:
    virtual void add_storage(IStorage* storage) = 0;

    virtual void remove_storage(IStorage* storage) = 0;

    virtual bool read(std::string &line) = 0;

    virtual ~IReader() = default;
};

#endif //OTUS_CPP_7_READER_H
