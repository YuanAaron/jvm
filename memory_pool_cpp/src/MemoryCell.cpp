//
// Created by oshacker on 10/25/22.
//

#include "../include/MemoryCell.h"

MemoryCell::MemoryCell() {

}

MemoryCell::MemoryCell(int start, int size):m_start(start), m_size(size) {
    m_end = start + size;
}

MemoryCell::~MemoryCell() {
    PRINT("[Cell信息]start=%d, end=%d, size=%d\n", m_start, m_end, m_size);
}

MemoryCell* MemoryCell::incStart(int step) {
    m_start += step;
    if (m_start > m_end) {
        ERROR_PRINT("cell start超过最大值\n");
    }
    return this;
}

MemoryCell* MemoryCell::decStart(int step) {
    m_start -= step;
    if (m_start < 0) {
        ERROR_PRINT("cell start小于0\n");
    }
    return this;
}

MemoryCell* MemoryCell::incSize(int step) {
    m_size += step;
    if (m_size > m_end) {
        ERROR_PRINT("cell size超过最大值\n");
    }
    return this;
}

MemoryCell* MemoryCell::decSize(int step) {
    m_size -= step;
    if (m_size < 0) {
        ERROR_PRINT("cell size小于0\n");
    }
    return this;
}

int MemoryCell::getStart() {
    return m_start;
}

int MemoryCell::getEnd() {
    return m_end;
}

int MemoryCell::getSize() {
    return m_size;
}

void MemoryCell::toString(string msg) {
    INFO_PRINT("[Cell信息]%s:start=%d, end=%d, size=%d\n", msg.c_str(), m_start, m_end, m_size);
}