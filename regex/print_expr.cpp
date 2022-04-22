#include <regex/print_expr.hpp>

#include <regex/expr.hpp>

#include <ostream>

std::ostream& operator<<(std::ostream& os, RE::Expr const* expr) {
    using Type = RE::Expr::Type;

    switch (expr->type()) {
    case Type::Epsilon:
        os << "empty";
        break;
    case Type::Literal:
        os << '\'' << expr->literal() << '\'';
        break;
    case Type::LiteralRange:
        os << '\'' << expr->range_first() << "'-'" << expr->range_last() << '\'';
        break;
    case Type::Star:
        os << '(' << expr->sub() << " star)";
        break;
    case Type::And:
        os << '(' << expr->left() << " and " << expr->right() << ')';
        break;
    case Type::Or:
        os << '(' << expr->left() << " or " << expr->right() << ')';
        break;
    }

    return os;
}
