cmake_minimum_required(VERSION 3.2)
project(PGSerialSocket)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

set(SOURCE_FILES main.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} pthread)
