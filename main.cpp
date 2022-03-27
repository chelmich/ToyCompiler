#include <regex/expr.hpp>
#include <regex/print_expr.hpp>

#include <iostream>

int main(int argc, char* argv[]) {
    RE::Expr *r = RE::Expr::And(
        RE::Expr::Literal('a'),
        RE::Expr::Star(RE::Expr::Literal('b')));

    std::cout << "regex: ";
    print_regex(std::cout, r);
    std::cout << '\n';

    return 0;
}
