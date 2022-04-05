#pragma once

template<typename T>
class NFA;
template<typename T>
class DFA;

/// @brief Convert a non-deterministic finite automata into a deterministic one
/// @details Uses the subset construction method. The resulting DFA is generally not minimal.
/// @related NFA
template<typename T>
DFA<T> nfa_to_dfa(NFA<T> const& nfa);
