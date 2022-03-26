#include <regex/expr.hpp>

#include <iostream>

// Recursively print a regular expression for debug
void print_regex(std::ostream& os, RE::Expr const* expr) {
    using Type = RE::Expr::Type;

    switch (expr->type()) {
    case Type::Epsilon:
        os << "empty";
        break;
    case Type::Literal:
        os << '\'' << expr->literal() << '\'';
        break;
    case Type::Star:
        os << '(';
        print_regex(os, expr->sub());
        os << " star)";
        break;
    case Type::And:
        os << '(';
        print_regex(os, expr->left());
        os << " and ";
        print_regex(os, expr->right());
        os << ')';
        break;
    case Type::Or:
        os << '(';
        print_regex(os, expr->left());
        os << " or ";
        print_regex(os, expr->right());
        os << ')';
        break;
    }
}

int main(int argc, char* argv[]) {
    RE::Expr *r = RE::Expr::And(
        RE::Expr::Literal('a'),
        RE::Expr::Star(RE::Expr::Literal('b')));

    std::cout << "regex: ";
    print_regex(std::cout, r);
    std::cout << '\n';

    return 0;
}
