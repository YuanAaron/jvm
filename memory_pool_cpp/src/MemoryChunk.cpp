//
// Created by oshacker on 10/25/22.
//

#include "../include/MemoryChunk.h"

MemoryChunk::MemoryChunk() {

}

MemoryChunk::MemoryChunk(int size, string filename, int line):m_size(size), m_filename(filename), m_line(line) {
    //32位平台占4byte,64位平台占8byte
    m_align_size = ALIGN_SIZE;
    m_max_cell_num = (m_size - 1) / m_align_size + 1;
    m_size = m_align_size * m_max_cell_num;

    INFO_PRINT("对齐:%d, cell数量:%d, 分配内存:%d\n", m_align_size, m_max_cell_num, m_size);

    m_remain_cell_num = m_max_cell_num;

    m_data = (char *)calloc(m_size, sizeof(char));
    NULL_CHECK(m_data);

    MemoryCell *cell = new MemoryCell(0,m_max_cell_num);
    m_available_table.push_front(cell);
}

MemoryChunk::~MemoryChunk() {
    PRINT("[调用析构函数%s]释放资源开始\n", __func__);

    if (m_data) {
        PRINT("\t 释放资源, 申请内存位置( %s:%d )，内存大小:%d 字节\n", m_filename.c_str(), m_line, m_size);
        delete m_data;
    }

    freeAvailableTable();
    freeUsedTable();

    PRINT("[调用析构函数%s]释放资源结束\n", __func__);
}

MemoryCell* MemoryChunk::alloc(int size) {
    MemoryCell *ret;
    if (size <= 0) {
        ERROR_PRINT("申请的内存大小需大于0\n");
    }

    int need_cell_num = (size - 1) / m_align_size + 1;
    if (need_cell_num > m_remain_cell_num) {
        ERROR_PRINT("申请的内存大小超过最大值\n");
    }

    //遍历available_table查找满足条件的MemoryCell
    list<MemoryCell *>::iterator available_iterator;
    for (available_iterator = m_available_table.begin(); available_iterator != m_available_table.end(); available_iterator++) {
        MemoryCell * cell = *available_iterator;
        if (cell->getSize() >= need_cell_num) {
            cell ->toString("找到了满足条件的Cell");
            ret = real_malloc(cell, need_cell_num);
            break;
        }
    }

    if (ret == NULL) {
        ERROR_PRINT("没有满足条件的Chunk(cell_num=%d)，无法分配内存，执行GC\n", need_cell_num);
    }
    return ret;
}

MemoryCell* MemoryChunk::real_malloc(MemoryCell *available_cell, unsigned cell_num) {
    //创建used_cell并加入list
    MemoryCell *usedCell = new MemoryCell(available_cell -> getStart(), cell_num);
    m_used_table.push_front(usedCell);

    //处理Cell
    available_cell ->incStart(cell_num) ->decSize(cell_num);

    //更新remain_cell_num
    decRemainCellNum(cell_num);
    return usedCell;
}

//MemoryChunk* MemoryChunk::incrRemainCellNum(int step) {
//    m_remain_cell_num += step;
//    if (m_remain_cell_num > m_max_cell_num) {
//        ERROR_PRINT("剩余的cell超过最大值\n");
//    }
//    return this;
//}

MemoryChunk* MemoryChunk::decRemainCellNum(int step) {
    m_remain_cell_num -= step;
    if (m_remain_cell_num < 0) {
        ERROR_PRINT("剩余的cell小于0\n");
    }
    return this;
}

void MemoryChunk::freeUsedTable() {
    PRINT("[释放used_table]开始\n");

    list<MemoryCell *>::iterator tmp;
    for (tmp = m_used_table.begin(); tmp != m_used_table.end(); tmp++) {
        delete (*tmp);
    }

    m_used_table.clear();

    PRINT("[释放used_table]结束\n");
}

void MemoryChunk::freeAvailableTable() {
    PRINT("[释放available_table]开始\n");

    list<MemoryCell *>::iterator tmp;
    for (tmp = m_available_table.begin(); tmp != m_available_table.end(); tmp++) {
        delete (*tmp);
    }

    m_available_table.clear();

    PRINT("[释放available_table]结束\n");
}

int MemoryChunk::getSize() {
    return m_size;
}

string* MemoryChunk::getFilename() {
    return &m_filename;
}

int MemoryChunk::getLine() {
    return m_line;
}