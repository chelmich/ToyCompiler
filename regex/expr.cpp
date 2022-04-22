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

Expr* Expr::AndMany(std::vector<Expr*> exprs) {
    assert(exprs.size() >= 2);
    for (Expr* expr : exprs) {
        assert(expr != nullptr);
    }
    return new Expr(Type::AndMany, exprs);
}

Expr* Expr::OrMany(std::vector<Expr*> exprs) {
    assert(exprs.size() >= 2);
    for (Expr* expr : exprs) {
        assert(expr != nullptr);
    }
    return new Expr(Type::OrMany, exprs);
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
    case Type::AndMany:
    case Type::OrMany:
        // Free vector expression
        for (Expr* expr : m_sub_vec) {
            delete expr;
        }
        m_sub_vec.~vector();
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

std::vector<Expr*> const& Expr::sub_vec() const {
    assert(m_type == Type::AndMany || m_type == Type::OrMany);
    return m_sub_vec;
}

}; // namespace RE
