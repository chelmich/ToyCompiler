#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <finite_automata/nfa.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    RE::Expr *r = RE::Expr::And(
        RE::Expr::Literal('a'),
        RE::Expr::Star(RE::Expr::Literal('b')));

    std::cout << "regex: " << r << '\n';

    NFA<char> nfa;
    nfa.add_state();
    nfa.add_state();
    nfa.set_initial_state(0);
    nfa.add_transition(0, 1, 'a');
    nfa.add_transition_epsilon(0, 1);

    return 0;
}
