cmake_minimum_required(VERSION 3.17)
project(rank_method)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(rank_method main.cpp select_support.cpp select_support.h)