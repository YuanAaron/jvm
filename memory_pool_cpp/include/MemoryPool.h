//
// Created by oshacker on 10/25/22.
//

#ifndef MEMORY_POOL_CPP_MEMORYPOOL_H
#define MEMORY_POOL_CPP_MEMORYPOOL_H

#include "common.h"
#include "MemoryChunk.h"

class MemoryPool {
private:
    list<MemoryChunk *> m_chunks;

public:
    MemoryPool();
    ~MemoryPool();

public:
    MemoryChunk* alloc(int size);

public:
    void checkMemoryLeak();
};

#endif //MEMORY_POOL_CPP_MEMORYPOOL_H
