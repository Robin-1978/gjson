cmake_minimum_required(VERSION 3.0)

project (gjson VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lemon lemon.c)

SET(GEN_SOURCES
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)

add_custom_command(
    OUTPUT ${GEN_SOURCES}
    COMMAND lemon -T${CMAKE_CURRENT_SOURCE_DIR}/lempar.c -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/parser.c ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEPENDS lemon lempar.c
)

add_library(gjson 
    gjson.cpp gjson.h ${GEN_SOURCES}
)


add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE gjson)