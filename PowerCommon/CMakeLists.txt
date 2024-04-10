cmake_minimum_required(VERSION 3.11)

project(PowerCommon VERSION 1.0)

include_directories(include)

file(GLOB_RECURSE SRCS src/*.c)

add_library(PowerCommon ${SRCS}
        src/PowerStream.c
        include/PowerStream.h)

install(TARGETS PowerCommon
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
