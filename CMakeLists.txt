cmake_minimum_required(VERSION 3.15)
project(HelloCpp)

set(CMAKE_CXX_STANDARD 17)

find_package(Matplot++ CONFIG REQUIRED)

add_executable(helloCPP helloCPP.cpp)

target_link_libraries(helloCPP PRIVATE Matplot++::matplot)