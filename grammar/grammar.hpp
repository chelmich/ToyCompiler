#pragma once

#include <grammar/terminal.hpp>
#include <grammar/nonterminal.hpp>

#include <vector>

class Grammar {
public:
    void add_terminal(GR::Terminal terminal) {
        m_terminals.push_back(std::move(terminal));
    }

    void add_nonterminal(GR::Nonterminal nonterminal) {
        m_nonterminals.push_back(std::move(nonterminal));
    }

    std::vector<GR::Terminal> const& terminals() const { return m_terminals; }
    std::vector<GR::Nonterminal> const& nonterminals() const { return m_nonterminals; }

private:
    std::vector<GR::Terminal> m_terminals;
    std::vector<GR::Nonterminal> m_nonterminals;
};
