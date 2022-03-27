#pragma once

#include <ostream>

template <typename T>
class NFA;

/// @brief Print NFA state and transition information for debug
/// @related NFA
template<typename T>
void print_nfa(std::ostream& os, NFA<T> const& nfa);
