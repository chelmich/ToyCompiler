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

    std::unordered_set<unsigned> const& accepting_states() const { return m_accepting_states; }

    /// Get the set of symbols a given state can transition on
    std::unordered_set<T> transition_symbols(unsigned state) const;
    /// Get the set of transition destinations for a given state and symbol
    std::unordered_set<unsigned> const& transitions_on(unsigned state, T symbol) const;
    /// Get the set of epsilon transition destinations for a given state
    std::unordered_set<unsigned> const& epsilon_transitions(unsigned state) const;

    /// @return Index of the newly added state
    unsigned add_state(bool accepting = false);

    /// Add a new transition on a given symbol
    void add_transition(unsigned from, unsigned to, T symbol);
    /// Add a new epsilon transition
    void add_transition_epsilon(unsigned from, unsigned to);

    /// Compute the set of states reachable from a given set by epsilon transitions
    std::unordered_set<unsigned> epsilon_closure(std::unordered_set<unsigned> states) const;

private:
    struct State {
        bool accepting;
        std::unordered_map<T, std::unordered_set<unsigned>> transitions;
        std::unordered_set<unsigned> epsilon_transitions;

        explicit State(bool accepting)
            : accepting(accepting) {}
    };

    std::vector<State> m_states;
    std::unordered_set<unsigned> m_accepting_states;
    std::optional<unsigned> m_initial_state;
};
