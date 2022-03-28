#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <finite_automata/dfa.hpp>
#include <finite_automata/nfa.hpp>
#include <finite_automata/print_dfa.hpp>
#include <finite_automata/print_nfa.hpp>

#include <regex_to_nfa.hpp>

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    RE::Expr* regex = RE::Expr::And(
        RE::Expr::Star(
            RE::Expr::Or(
                RE::Expr::Literal('a'),
                RE::Expr::Literal('b'))),
        RE::Expr::And(
            RE::Expr::Literal('a'),
            RE::Expr::Literal('c')));

    std::cout << "Regex: " << regex << "\n\n";

    NFA<char> nfa = regex_to_nfa(regex);

    std::cout << "NFA:\n";
    print_nfa(std::cout, nfa);
    std::cout << '\n';

    std::ofstream nfa_graph_file("nfa.gv");
    print_nfa_graphviz(nfa_graph_file, nfa);
    nfa_graph_file.close();

    DFA<char> dfa;
    dfa.add_state();
    dfa.set_initial_state(0);
    dfa.add_state();
    dfa.add_state(true);
    dfa.add_transition(0, 1, 'a');
    dfa.add_transition(0, 1, 'b');
    dfa.add_transition(1, 2, 'c');

    std::cout << "DFA:\n";
    print_dfa(std::cout, dfa);
    std::cout << '\n';

    std::ofstream dfa_graph_file("dfa.gv");
    print_dfa_graphviz(dfa_graph_file, dfa);
    dfa_graph_file.close();

    return 0;
}
