#include <regex/regex.hpp>

#include <finite_automata/nfa.hpp>
#include <finite_automata/nfa_to_dfa.hpp>

#include <regex/expr.hpp>
#include <regex/regex_to_nfa.hpp>

#include <cassert>

Regex::Regex(RE::Expr* expression)
    : m_expr(expression)
{
    assert(expression != nullptr);

    NFA<char> nfa = regex_to_nfa(m_expr);
    m_dfa = nfa_to_dfa(nfa);

    assert(m_dfa.has_initial_state());
}

Regex::~Regex() {
    delete m_expr;
}

bool Regex::match(std::string_view input) const {
    std::optional<size_t> result = match_partial(input);

    if (!result.has_value()) return false;

    // Must match the whole string
    return result.value() == input.length();
}

std::optional<size_t> Regex::match_partial(std::string_view input) const {
    unsigned current_state = m_dfa.initial_state().value();

    bool found_match = false;
    size_t longest_match = 0;

    size_t i;
    for (i = 0; i < input.length(); i++) {
        const char current_char = input[i];

        // Check if the current state indicates a match
        if (m_dfa.accepting_states().contains(current_state)) {
            found_match = true;
            longest_match = i;
        }

        // Take the transition for the current character if one exists
        if (m_dfa.transitions(current_state).contains(current_char)) {
            current_state = m_dfa.transitions(current_state).at(current_char);
        } else {
            break; // no matching transition
        }
    }

    // Check if the final state matches
    if (m_dfa.accepting_states().contains(current_state)) {
        found_match = true;
        longest_match = i;
    }

    if (found_match) {
        return longest_match;
    } else {
        return {};
    }
}
