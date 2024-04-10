cmake_minimum_required(VERSION 3.11)

project(PowerServer VERSION 1.0)

find_package(PostgreSQL REQUIRED)

include_directories(include)

include_directories(${CMAKE_SOURCE_DIR}/PowerCommon)

file(GLOB_RECURSE SRCS src/*.c)

add_executable(PowerServer ${SRCS}
        src/PowerContext.c
        include/PowerContext.h
        src/utils.c
        include/utils.h)

target_include_directories(PowerServer PRIVATE ${PostgreSQL_INCLUDE_DIRS})

target_link_libraries(PowerServer PowerCommon ${PostgreSQL_LIBRARIES})
