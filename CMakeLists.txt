cmake_minimum_required(VERSION 3.0)

project (gjson VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lemon ${CMAKE_CURRENT_SOURCE_DIR}/sqlite/tool/lemon.c)
add_subdirectory(RE-flex)
add_definitions("-g") 

SET(GEN_PARSER
    ${CMAKE_CURRENT_BINARY_DIR}/parser.c
    ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)

SET(GEN_LEXER
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/lexer.h
)


add_custom_command(
    OUTPUT ${GEN_PARSER}
    COMMAND lemon -T${CMAKE_CURRENT_SOURCE_DIR}/sqlite/tool/lempar.c -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    #COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/parser.c ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
    VERBATIM
)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/parser.c PROPERTIES LANGUAGE CXX )

add_custom_command(
    OUTPUT ${GEN_LEXER}
    COMMAND RE-flex/reflex --outfile=lexer.cpp --header-file=lexer.h ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
    VERBATIM
)

SET(GEN_JSON_PARSER
    ${CMAKE_CURRENT_BINARY_DIR}/json.c
    ${CMAKE_CURRENT_BINARY_DIR}/json.h
)

SET(GEN_JSON_LEXER
    ${CMAKE_CURRENT_BINARY_DIR}/json_lexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/json_lexer.h
)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/json.c PROPERTIES LANGUAGE CXX )
add_custom_command(
    OUTPUT ${GEN_JSON_PARSER}
    COMMAND lemon -T${CMAKE_CURRENT_SOURCE_DIR}/sqlite/tool/lempar.c -d${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/json.y
    #COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/json.c ${CMAKE_CURRENT_BINARY_DIR}/json.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/json.y
    VERBATIM
)

add_custom_command(
    OUTPUT ${GEN_JSON_LEXER}
    COMMAND RE-flex/reflex --outfile=json_lexer.cpp --header-file=json_lexer.h ${CMAKE_CURRENT_SOURCE_DIR}/json.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/json.l
    VERBATIM
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(gjson 
    gjson.cpp gjson.h calc.cpp calc.h ${GEN_PARSER} ${GEN_LEXER} ${GEN_JSON_PARSER} ${GEN_JSON_LEXER}
)


add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE gjson ReflexLibStatic)

add_executable(json_example json_example.cpp)
target_link_libraries(json_example PRIVATE gjson ReflexLibStatic profiler)

