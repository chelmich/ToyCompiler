#pragma once

#include <ostream>

template <typename T>
class NFA;

/// @brief Print NFA state and transition information for debug
/// @related NFA
template<typename T>
void print_nfa(std::ostream& os, NFA<T> const& nfa);

/// @brief Print a graphviz representation of an NFA for debug
/// @related NFA
template<typename T>
void print_nfa_graphviz(std::ostream& os, NFA<T> const& nfa);
