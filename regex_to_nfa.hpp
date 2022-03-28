#pragma once

namespace RE {
class Expr;
}

template<typename T>
class NFA;

/// @brief Convert a regular expression into a non-deterministic finite automata
/// @related RE::Expr
NFA<char> regex_to_nfa(RE::Expr const* regex);
