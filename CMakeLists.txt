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
        finite_automata/dfa.cpp
        finite_automata/nfa.cpp
        finite_automata/nfa_to_dfa.cpp
        finite_automata/print_dfa.cpp
        finite_automata/print_nfa.cpp
        regex/expr.cpp
        regex/print_expr.cpp
        regex/regex.cpp
        regex/regex_to_nfa.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
