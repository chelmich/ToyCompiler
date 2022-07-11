#pragma once

#include <finite_automata/dfa.hpp>

#include <optional>
#include <string_view>

namespace RE {
class Expr;
}

/// Regular expression that supports string matching
class Regex {
public:
    /// Takes ownership of an expression tree
    explicit Regex(RE::Expr* expression);

    ~Regex();

    // Delete copy constructor and copy assignment
    Regex(Regex const&) = delete;
    Regex& operator=(Regex const&) = delete;

    // Move constructor and move assignment
    Regex(Regex&& other);
    Regex& operator=(Regex&& other);

    RE::Expr const* expr() const { return m_expr; }
    DFA<char> const& dfa() const { return m_dfa; }

    /// @brief Check if this regular expression matches a given string
    /// @returns @c true if the entire string matches, @c false otherwise
    bool match(std::string_view input) const;

    /// @brief Find the longest match starting at the beginning of a given string
    /// @returns The number of characters matched if a match exists, @c std::nullopt otherwise
    std::optional<size_t> match_partial(std::string_view input) const;

private:
    RE::Expr* m_expr;
    DFA<char> m_dfa;
};
