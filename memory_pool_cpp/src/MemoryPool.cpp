//
// Created by oshacker on 10/25/22.
//

#include "../include/MemoryPool.h"

MemoryPool::MemoryPool() {

}

MemoryPool::~MemoryPool() {
    INFO_PRINT("[释放内存]开始\n");

    list<MemoryChunk *>::iterator iterator;
    for (iterator = m_chunks.begin(); iterator != m_chunks.end(); iterator++) {
        delete *iterator;
    }
    m_chunks.clear();
    INFO_PRINT("[释放内存]结束\n");
}

MemoryChunk* MemoryPool::alloc(int size) {
    MemoryChunk *chunk = new MemoryChunk(size, __FILE__, __LINE__);
    m_chunks.push_back(chunk);
    return chunk;
}

void MemoryPool::checkMemoryLeak() {
    INFO_PRINT("[打印未释放的内存]开始\n");

    list<MemoryChunk *>::iterator iterator;
    for (iterator = m_chunks.begin(); iterator != m_chunks.end(); iterator++) {
        MemoryChunk *chunk = *iterator;

        INFO_PRINT("\t [未释放的内存]申请位置:( %s:%d ), 内存大小:%d 字节\n",
                   chunk->getFilename()->c_str(), chunk->getLine(), chunk->getSize());
    }

    INFO_PRINT("[打印未释放的内存]结束\n");
}
