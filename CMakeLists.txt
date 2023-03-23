cmake_minimum_required(VERSION 3.5)

project(alg3-elgamal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(alg3-elgamal main.cpp)

install(TARGETS alg3-elgamal
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
