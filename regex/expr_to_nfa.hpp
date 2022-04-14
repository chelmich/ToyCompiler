#pragma once

namespace RE {
class Expr;
}

template<typename T>
class NFA;

/// @brief Convert a regular expression tree into a non-deterministic finite automata
/// @related RE::Expr
NFA<char> expr_to_nfa(RE::Expr const* regex);
