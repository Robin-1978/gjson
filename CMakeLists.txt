cmake_minimum_required(VERSION 3.0)

project (gjson VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)


add_executable(lemon ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/tool/lemon.c)
add_subdirectory(RE-flex)

SET(GEN_PARSER
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)

SET(GEN_LEXER
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.h
)

add_custom_command(
    OUTPUT ${GEN_PARSER}
    COMMAND lemon -T${CMAKE_CURRENT_SOURCE_DIR}/sqlite/tool/lempar.c -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/parser.c ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    VERBATIM
)

add_custom_command(
    OUTPUT ${GEN_LEXER}
    COMMAND RE-flex/reflex −−outfile=lexer.cpp --header-file=lexer.h ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
    VERBATIM
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(gjson 
    gjson.cpp gjson.h jparser.cpp jparser.h ${GEN_PARSER} ${GEN_LEXER}
)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE gjson ReflexLibStatic)