#pragma once

namespace RE {

/// Tree representation of a regular expression
class Expr {
public:
    enum class Type {
        Epsilon,
        Literal,
        // Unary expressions
        Star,
        // Binary expressions
        And,
        Or,
    };

    static Expr* Epsilon();
    static Expr* Literal(char literal);
    static Expr* Star(Expr* sub);
    static Expr* And(Expr* left, Expr* right);
    static Expr* Or(Expr* left, Expr* right);

    // Delete copy constructor and copy assignment
    Expr(Expr const&) = delete;
    Expr& operator=(Expr const&) = delete;

    /// Recursively frees all subexpressions (if any)
    ~Expr();

    Type type() const { return m_type; }

    char literal() const;
    Expr* sub() const;
    Expr* left() const;
    Expr* right() const;

private:
    /// Private constructor for an epsilon expression
    explicit Expr()
        : m_type(Type::Epsilon) {}

    /// Private constructor for a literal character
    explicit Expr(char literal)
        : m_type(Type::Literal)
        , m_literal(literal) {}

    /// Private constructor for a unary expression
    Expr(Type type, Expr* sub)
        : m_type(type)
        , m_sub(sub) {}

    /// Private constructor for a binary expression
    Expr(Type type, Expr* left, Expr* right)
        : m_type(type)
        , m_left(left)
        , m_right(right) {}

    Type m_type;

    union {
        // Valid for Type::Literal
        char m_literal;

        // Valid for Type::Star
        Expr* m_sub;

        // Valid for Type::And, Type::Or
        struct {
            Expr* m_left;
            Expr* m_right;
        };
    };
};

} // namespace RE
