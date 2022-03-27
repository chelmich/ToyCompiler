cmake_minimum_required(VERSION 3.16)

project(compiler LANGUAGES CXX)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED on
)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        finite_automata/nfa.cpp
        regex/expr.cpp
        regex/print_expr.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
