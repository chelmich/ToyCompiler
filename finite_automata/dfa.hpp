#pragma once

#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/// @brief Deterministic finite automata
/// @tparam T Type of symbol to label transitions with
template<typename T>
class DFA {
public:
    std::optional<unsigned> initial_state() const { return m_initial_state; }
    bool has_initial_state() const { return m_initial_state.has_value(); }
    void set_initial_state(unsigned state);

    unsigned num_states() const { return m_states.size(); }

    std::unordered_set<unsigned> const& accepting_states() const { return m_accepting_states; }

    /// Get the map of transitions for a given state
    std::unordered_map<T, unsigned> transitions(unsigned state) const;

    /// @return Index of the newly added state
    unsigned add_state(bool accepting = false);

    /// Add a new transition on a given symbol
    void add_transition(unsigned from, unsigned to, T symbol);

private:
    struct State {
        bool accepting;
        std::unordered_map<T, unsigned> transitions;

        explicit State(bool accepting)
            : accepting(accepting) {}
    };

    std::vector<State> m_states;
    std::unordered_set<unsigned> m_accepting_states;
    std::optional<unsigned> m_initial_state;
};
