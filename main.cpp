#include <grammar/terminal.hpp>

#include <regex/regex.hpp>
#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    Regex regex = Regex(RE::Expr::Star(RE::Expr::LiteralRange('a', 'z')));

    std::cout << "Regex: " << regex.expr() << "\n\n";

    std::vector<std::string> test_strings = {"abc", "ABC", "abcDef", ""};
    for (auto const& str : test_strings) {
        std::cout << '"' << str << "\"\n";
        std::cout << "   Matches? " << (regex.match(str) ? "true" : "false") << '\n';
        std::optional<size_t> partial = regex.match_partial(str);
        std::cout << "   Partial match? ";
        if (partial.has_value()) {
            std::cout << "true, " << partial.value() << " characters\n";
        } else {
            std::cout << "false\n";
        }
    }
    std::cout << '\n';

    std::vector<GR::Terminal> terminals;
    terminals.push_back(GR::Terminal("Equals", Regex(RE::Expr::Literal('='))));
    terminals.push_back(GR::Terminal("Number", Regex(
        RE::Expr::And(
            RE::Expr::LiteralRange('1', '9'),
            RE::Expr::Star(
                RE::Expr::LiteralRange('0', '9'))))));
    terminals.push_back(GR::Terminal("Identifier", Regex(
        RE::Expr::And(
            RE::Expr::Or(
                RE::Expr::LiteralRange('a', 'z'),
                RE::Expr::LiteralRange('A', 'Z')),
            RE::Expr::Star(
                RE::Expr::Or(
                    RE::Expr::LiteralRange('a', 'z'),
                    RE::Expr::Or(
                        RE::Expr::LiteralRange('A', 'Z'),
                        RE::Expr::LiteralRange('0', '9'))))))));

    for (GR::Terminal const& terminal : terminals) {
        std::cout << terminal.name() << ": " << terminal.regex().expr() << '\n';
    }

    return 0;
}
