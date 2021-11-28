cmake_minimum_required(VERSION 3.20)
project(BigInteger)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigInteger BigInteger.cpp biginteger.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g")
