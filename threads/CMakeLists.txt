cmake_minimum_required(VERSION 3.12)
project(threads)

set(CMAKE_CXX_STANDARD 14)

add_executable(threads main.cpp workers.h++)

TARGET_LINK_LIBRARIES(
        threads
        pthread
)