#include <regex/regex.hpp>
#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

    std::vector<std::string> test_strings = {"ac", "babbac", "abbacd", "dac", ""};
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

    return 0;
}
