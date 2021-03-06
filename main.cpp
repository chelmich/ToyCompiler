#include <grammar/grammar.hpp>
#include <grammar/terminal.hpp>

#include <regex/regex.hpp>
#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    Grammar grammar;

    grammar.add_terminal(GR::Terminal("Equals", Regex(RE::Expr::Literal('='))));
    grammar.add_terminal(GR::Terminal("Number", Regex(
        RE::Expr::And(
            RE::Expr::LiteralRange('1', '9'),
            RE::Expr::Star(
                RE::Expr::LiteralRange('0', '9'))))));
    grammar.add_terminal(GR::Terminal("Identifier", Regex(
        RE::Expr::And(
            RE::Expr::OrMany({
                RE::Expr::Literal('_'),
                RE::Expr::LiteralRange('a', 'z'),
                RE::Expr::LiteralRange('A', 'Z')}),
            RE::Expr::Star(
                RE::Expr::OrMany({
                    RE::Expr::Literal('_'),
                    RE::Expr::LiteralRange('a', 'z'),
                    RE::Expr::LiteralRange('A', 'Z'),
                    RE::Expr::LiteralRange('0', '9')}))))));
    grammar.add_terminal(GR::Terminal("While", Regex(
        RE::Expr::AndMany({
            RE::Expr::Literal('w'),
            RE::Expr::Literal('h'),
            RE::Expr::Literal('i'),
            RE::Expr::Literal('l'),
            RE::Expr::Literal('e')}))));

    for (GR::Terminal const& terminal : grammar.terminals()) {
        std::cout << terminal.name() << ": " << terminal.regex().expr() << '\n';
    }
    std::cout << '\n';

    std::vector<std::string> test_strings = {"foo_barBaz", "FOO24", "__main__", "foo?bar", "74test", ""};
    for (auto const& str : test_strings) {
        std::cout << '"' << str << "\"\n";
        std::cout << "   Matches? " << (grammar.terminals()[2].regex().match(str) ? "true" : "false") << '\n';
        std::optional<size_t> partial = grammar.terminals()[2].regex().match_partial(str);
        std::cout << "   Partial match? ";
        if (partial.has_value()) {
            std::cout << "true, " << partial.value() << " characters\n";
        } else {
            std::cout << "false\n";
        }
    }

    return 0;
}
