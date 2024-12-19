cmake_minimum_required(VERSION 3.30)
project(BinaryTreePerfomance)
INCLUDE(FindPkgConfig)


set(CMAKE_CXX_STANDARD 20)

find_package(raylib ${RAYLIB_VERSION} QUIET)

add_executable(BinaryTreePerfomance main.cpp
        Tree.h
        Node.h)

target_link_libraries(BinaryTreePerfomance PRIVATE raylib)
