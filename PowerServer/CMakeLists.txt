cmake_minimum_required(VERSION 3.11)

project(PowerServer VERSION 1.0)

include_directories(include)

include_directories(${CMAKE_SOURCE_DIR}/PowerCommon)

file(GLOB SRCS src/*.c)

add_executable(PowerServer ${SRCS})

target_link_libraries(PowerServer PowerCommon)
