cmake_minimum_required(VERSION 3.5)

project(FormalLanguages-Test)

file(GLOB_RECURSE SOURCES . source/*.cpp)

add_executable(Test ${SOURCES})
    
target_include_directories(Test PUBLIC "./include")

target_link_libraries(Test PUBLIC General)