#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <finite_automata/nfa.hpp>
#include <finite_automata/print_nfa.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    RE::Expr *r = RE::Expr::And(
        RE::Expr::Literal('a'),
        RE::Expr::Star(RE::Expr::Literal('b')));

    std::cout << "Regex: " << r << '\n';

    NFA<char> nfa;
    nfa.add_state();
    nfa.add_state(true);
    nfa.set_initial_state(0);
    nfa.add_transition(0, 1, 'a');
    nfa.add_transition_epsilon(0, 1);

    std::cout << "NFA:\n";
    print_nfa(std::cout, nfa);

    return 0;
}
