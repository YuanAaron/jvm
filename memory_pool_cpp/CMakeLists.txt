cmake_minimum_required(VERSION 3.23)
project(memory_pool_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(memory_pool_cpp main.cpp src/MemoryPool.cpp include/MemoryPool.h src/MemoryChunk.cpp include/MemoryChunk.h src/MemoryCell.cpp include/MemoryCell.h include/common.h)
