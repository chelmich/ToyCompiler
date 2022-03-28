#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <finite_automata/nfa.hpp>
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

    std::cout << "Regex: " << regex << '\n';

    NFA<char> nfa = regex_to_nfa(regex);

    std::cout << "NFA:\n";
    print_nfa(std::cout, nfa);

    std::ofstream graph_file("nfa.gv");
    print_nfa_graphviz(graph_file, nfa);
    graph_file.close();

    return 0;
}
