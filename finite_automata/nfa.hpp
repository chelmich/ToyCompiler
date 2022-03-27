#pragma once

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/// Non-deterministic finite automata
template<typename T>
class NFA {
public:
    std::optional<unsigned> initial_state() const { return m_initial_state; }
    bool has_initial_state() const { return m_initial_state.has_value(); }
    void set_initial_state(unsigned state);

    unsigned num_states() const { return m_states.size(); }

    /// @return Index of the newly added state
    unsigned add_state();

    void add_transition(unsigned from, unsigned to, T symbol);
    void add_transition_epsilon(unsigned from, unsigned to);

private:
    struct State {
        std::unordered_map<T, std::unordered_set<unsigned>> transitions;
        std::unordered_set<unsigned> epsilon_transitions;
    };

    std::vector<State> m_states;
    std::optional<unsigned> m_initial_state;
};
