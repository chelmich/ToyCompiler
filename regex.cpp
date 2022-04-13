#include <regex.hpp>

#include <finite_automata/nfa.hpp>
#include <finite_automata/nfa_to_dfa.hpp>

#include <regex/expr.hpp>
#include <regex_to_nfa.hpp>

#include <cassert>

Regex::Regex(RE::Expr* expression)
    : m_expr(expression)
{
    assert(expression != nullptr);

    NFA<char> nfa = regex_to_nfa(m_expr);
    m_dfa = nfa_to_dfa(nfa);
}

Regex::~Regex() {
    delete m_expr;
}
