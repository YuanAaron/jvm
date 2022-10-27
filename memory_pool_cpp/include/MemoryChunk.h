//
// Created by oshacker on 10/25/22.
//

#ifndef MEMORY_POOL_CPP_MEMORYCHUNK_H
#define MEMORY_POOL_CPP_MEMORYCHUNK_H

#include "common.h"
#include "MemoryCell.h"

class MemoryChunk {
private:
    //实际申请的内存大小
    int m_size;
    //内存对齐
    int m_align_size;
    //数据真实存放的地方
    char* m_data;
    //该chunk有多少cell
    int m_max_cell_num;
    //该chunk剩余多少cell
    int m_remain_cell_num;

private:
    //已使用的内存列表
    list<MemoryCell *> m_used_table;
    //可供使用的内存列表
    list<MemoryCell *> m_available_table;

private:
    string m_filename;
    int m_line;

public:
    MemoryChunk();
    MemoryChunk(int size, string filename, int line);
    ~MemoryChunk();

public:
    MemoryCell* alloc(int size);
private:
    MemoryCell* real_malloc(MemoryCell *available_cell,unsigned cell_num);

public:
//    MemoryChunk* incrRemainCellNum(int step);
    MemoryChunk* decRemainCellNum(int step);

    void freeAvailableTable();
    void freeUsedTable();

    int getSize();
    string* getFilename();
    int getLine();
};

#endif //MEMORY_POOL_CPP_MEMORYCHUNK_H
