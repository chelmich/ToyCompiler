#pragma once

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/// @brief Non-deterministic finite automata
/// @tparam T Type of symbol to label transitions with
template<typename T>
class NFA {
public:
    std::optional<unsigned> initial_state() const { return m_initial_state; }
    bool has_initial_state() const { return m_initial_state.has_value(); }
    void set_initial_state(unsigned state);

    unsigned num_states() const { return m_states.size(); }

    /// Get the set of symbols a given state can transition on
    std::unordered_set<T> transition_symbols(unsigned state) const;
    /// Get the set of transition destinations for a given state and symbol
    std::unordered_set<unsigned> transitions_on(unsigned state, T symbol) const;
    /// Get the set of epsilon transition destinations for a given state
    std::unordered_set<unsigned> epsilon_transitions(unsigned state) const;

    /// @return Index of the newly added state
    unsigned add_state();

    /// Add a new transition on a given symbol
    void add_transition(unsigned from, unsigned to, T symbol);
    /// Add a new epsilon transition
    void add_transition_epsilon(unsigned from, unsigned to);

private:
    struct State {
        std::unordered_map<T, std::unordered_set<unsigned>> transitions;
        std::unordered_set<unsigned> epsilon_transitions;
    };

    std::vector<State> m_states;
    std::optional<unsigned> m_initial_state;
};
