#pragma once

#include <ostream>

namespace RE {
class Expr;
}

/// @brief Recursively print a regular expression for debug
/// @related RE::Expr
void print_regex(std::ostream& os, RE::Expr const* expr);
