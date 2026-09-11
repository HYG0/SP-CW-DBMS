cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(DBMS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLEX 2.6 REQUIRED)
find_package(BISON 3.0 REQUIRED)
find_package(Boost REQUIRED COMPONENTS container date_time)
find_package(nlohmann_json REQUIRED)

add_library(dbms_b_plus_tree INTERFACE)
target_include_directories(dbms_b_plus_tree
        INTERFACE
        include
        include/core/tree)
target_link_libraries(dbms_b_plus_tree
        INTERFACE
        Boost::container)

# Bison & Flex
FLEX_TARGET(Lexer src/query/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
BISON_TARGET(Parser src/query/parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set(CORE_SOURCES
        src/core/value.cpp
        src/core/schema.cpp
        src/core/table.cpp
        src/core/database.cpp
        src/core/dbms.cpp
        src/core/stringpool.cpp
        src/storage/binary_io.cpp
        src/storage/pager.cpp
        src/storage/page_io.cpp
        src/storage/serializer.cpp
        src/storage/storage_manager.cpp
        ${FLEX_Lexer_OUTPUTS}
        ${BISON_Parser_OUTPUTS}
)

set(CORE_INCLUDE_DIRS
        include
        ${CMAKE_CURRENT_BINARY_DIR})

if (FLEX_INCLUDE_DIRS)
    list(APPEND CORE_INCLUDE_DIRS ${FLEX_INCLUDE_DIRS})
endif ()

set(CORE_LIBS
        dbms_b_plus_tree
        Boost::container
        nlohmann_json::nlohmann_json)

add_library(dbms_core ${CORE_SOURCES})
target_include_directories(dbms_core
        PUBLIC
        ${CORE_INCLUDE_DIRS})
target_link_libraries(dbms_core
        PUBLIC
        ${CORE_LIBS})

# CLI
add_executable(dbms src/main.cpp)
target_link_libraries(dbms PRIVATE dbms_core)

# Tests
enable_testing()
add_subdirectory(tests)
