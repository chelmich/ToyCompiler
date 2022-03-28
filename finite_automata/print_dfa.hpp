#pragma once

#include <ostream>

template <typename T>
class DFA;

/// @brief Print DFA state and transition information for debug
/// @related DFA
template<typename T>
void print_dfa(std::ostream& os, DFA<T> const& dfa);

/// @brief Print a graphviz representation of a DFA for debug
/// @related DFA
template<typename T>
void print_dfa_graphviz(std::ostream& os, DFA<T> const& dfa);
