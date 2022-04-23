#pragma once

#include <string>

namespace GR {

/// Nonterminal symbol for a context-free grammar
class Nonterminal {
public:
    explicit Nonterminal(std::string name)
        : m_name(name) {}

    std::string const& name() const { return m_name; }

private:
    std::string m_name;
};

} // namespace GR
