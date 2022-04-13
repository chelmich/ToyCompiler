#pragma once

#include <finite_automata/dfa.hpp>

namespace RE {
class Expr;
}

class Regex {
public:
    /// Takes ownership of an expression tree
    explicit Regex(RE::Expr* expression);

    ~Regex();

    // Delete copy constructor and copy assignment
    Regex(Regex const&) = delete;
    Regex& operator=(Regex const&) = delete;

    RE::Expr const* expr() const { return m_expr; }
    DFA<char> const& dfa() const { return m_dfa; }

private:
    RE::Expr* m_expr;
    DFA<char> m_dfa;
};
