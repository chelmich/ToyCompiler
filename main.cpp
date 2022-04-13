#include <regex.hpp>

#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <finite_automata/dfa.hpp>
#include <finite_automata/nfa.hpp>
#include <finite_automata/nfa_to_dfa.hpp>
#include <finite_automata/print_dfa.hpp>
#include <finite_automata/print_nfa.hpp>

#include <regex_to_nfa.hpp>

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    Regex regex = Regex(RE::Expr::And(
        RE::Expr::Star(
            RE::Expr::Or(
                RE::Expr::Literal('a'),
                RE::Expr::Literal('b'))),
        RE::Expr::And(
            RE::Expr::Literal('a'),
            RE::Expr::Literal('c'))));

    std::cout << "Regex: " << regex.expr() << "\n\n";

    NFA<char> nfa = regex_to_nfa(regex.expr());

    std::cout << "NFA:\n";
    print_nfa(std::cout, nfa);
    std::cout << '\n';

    std::ofstream nfa_graph_file("nfa.gv");
    print_nfa_graphviz(nfa_graph_file, nfa);
    nfa_graph_file.close();

    auto e_closure = nfa.epsilon_closure({0});
    std::cout << "epsilon closure of s0 =";
    for (unsigned state : e_closure) {
        std::cout << " s" << state;
    }
    std::cout << "\n\n";

    DFA<char> dfa = nfa_to_dfa(nfa);

    std::cout << "DFA:\n";
    print_dfa(std::cout, dfa);
    std::cout << '\n';

    std::ofstream dfa_graph_file("dfa.gv");
    print_dfa_graphviz(dfa_graph_file, dfa);
    dfa_graph_file.close();

    return 0;
}
