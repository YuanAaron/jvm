#include <iostream>

#include "include/MemoryPool.h"

/**
 * 内存池
 * @return
 */
int main() {
    MemoryPool *memoryPool = new MemoryPool();
    MemoryChunk *chunk = memoryPool -> alloc(25);
    chunk->alloc(1);
    chunk->alloc(10);

//    chunk = memoryPool -> alloc(78);
//    chunk->alloc(41);
//
//    memoryPool -> alloc(19);

    memoryPool -> checkMemoryLeak();
    delete memoryPool;

    return 0;
}
