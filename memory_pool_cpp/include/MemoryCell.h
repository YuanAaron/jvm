//
// Created by oshacker on 10/25/22.
//

#ifndef MEMORY_POOL_CPP_MEMORYCELL_H
#define MEMORY_POOL_CPP_MEMORYCELL_H

#include "common.h"

class MemoryCell {
private:
    int m_start;
    int m_end;
    //Cell的数量（每个Cell占 ALIGN_SIZE 字节）
    int m_size;

public:
    MemoryCell();
    MemoryCell(int start, int size);
    ~MemoryCell();

    MemoryCell* incStart(int step);
    MemoryCell* decStart(int step);
    MemoryCell* incSize(int step);
    MemoryCell* decSize(int step);

    int getStart();
    int getEnd();
    int getSize();

    void toString(string msg);
};

#endif //MEMORY_POOL_CPP_MEMORYCELL_H
