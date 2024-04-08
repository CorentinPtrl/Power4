cmake_minimum_required(VERSION 3.11)

project(PowerClient VERSION 1.0)

find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

include_directories(include)

include_directories(${CMAKE_SOURCE_DIR}/PowerCommon)

file(GLOB SRCS src/*.c)

add_executable(PowerClient ${SRCS})

target_link_libraries(PowerClient PowerCommon sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
