cmake_minimum_required(VERSION 3.12)
project(bpptree)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Jsoncpp  REQUIRED)

message(STATUS "JSONCPP_INCLUDE_DIR ${JSONCPP_INCLUDE_DIR}")
message(STATUS "JSONCPP_LIBRARY     ${JSONCPP_LIBRARY}")


add_executable(bpptree main.cpp
        Bpptree.h
        Bpptree.cpp
        )

target_include_directories(bpptree PUBLIC ${JSONCPP_INCLUDE_DIR})
target_link_libraries(bpptree PUBLIC ${JSONCPP_LIBRARY})