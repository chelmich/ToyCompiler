#include <regex/expr.hpp>

#include <cassert>

namespace RE {

Expr* Expr::Epsilon() {
    return new Expr();
}

Expr* Expr::Literal(char literal) {
    return new Expr(literal);
}

Expr* Expr::LiteralRange(char first, char last) {
    assert(first < last);
    return new Expr(first, last);
}

Expr* Expr::Star(Expr* sub) {
    assert(sub != nullptr);
    return new Expr(Type::Star, sub);
}

Expr* Expr::And(Expr* left, Expr* right) {
    assert(left != nullptr && right != nullptr);
    return new Expr(Type::And, left, right);
}

Expr* Expr::Or(Expr* left, Expr* right) {
    assert(left != nullptr && right != nullptr);
    return new Expr(Type::Or, left, right);
}

Expr::~Expr() {
    switch (m_type) {
    case Type::Epsilon:
    case Type::Literal:
    case Type::LiteralRange:
        // Do nothing
        break;
    case Type::Star:
        // Free unary expression
        delete m_sub;
        break;
    case Type::And:
    case Type::Or:
        // Free binary expression
        delete m_left;
        delete m_right;
        break;
    }
}

char Expr::literal() const {
    assert(m_type == Type::Literal);
    return m_literal;
}

char Expr::range_first() const {
    assert(m_type == Type::LiteralRange);
    return m_literal_first;
}

char Expr::range_last() const {
    assert(m_type == Type::LiteralRange);
    return m_literal_last;
}

Expr* Expr::sub() const {
    assert(m_type == Type::Star);
    return m_sub;
}

Expr* Expr::left() const {
    assert(m_type == Type::And || m_type == Type::Or);
    return m_left;
}

Expr* Expr::right() const {
    assert(m_type == Type::And || m_type == Type::Or);
    return m_right;
}

}; // namespace RE
