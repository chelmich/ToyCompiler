#pragma once

#include <ostream>

namespace RE {
class Expr;
}

/// @brief Recursively print a regular expression for debug
/// @related RE::Expr
std::ostream& operator<<(std::ostream& os, RE::Expr const* expr);
