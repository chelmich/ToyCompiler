#include <finite_automata/nfa.hpp>

#include <cassert>

template<typename T>
void NFA<T>::set_initial_state(unsigned state) {
    assert(state < m_states.size()); // state index must be valid
    m_initial_state = state;
}

template<typename T>
std::unordered_set<T> NFA<T>::transition_symbols(unsigned state) const {
    assert(state < m_states.size()); // state index must be valid
    std::unordered_set<T> symbols;
    for (auto const& pair : m_states[state].transitions) {
        symbols.insert(pair.first);
    }
    return symbols;
}

template<typename T>
std::unordered_set<unsigned> NFA<T>::transitions_on(unsigned state, T symbol) const {
    assert(state < m_states.size()); // state index must be valid
    assert(m_states[state].transitions.contains(symbol));
    return m_states[state].transitions.at(symbol);
}

template<typename T>
std::unordered_set<unsigned> NFA<T>::epsilon_transitions(unsigned state) const {
    assert(state < m_states.size()); // state index must be valid
    return m_states[state].epsilon_transitions;
}

template<typename T>
unsigned NFA<T>::add_state(bool accepting) {
    const unsigned state = m_states.size();
    m_states.push_back(State(accepting));
    if (accepting) m_accepting_states.insert(state);
    return state;
}

template<typename T>
void NFA<T>::add_transition(unsigned from, unsigned to, T symbol) {
    assert(from < m_states.size() && to < m_states.size()); // state indices must be valid
    m_states[from].transitions[symbol].insert(to);
}

template<typename T>
void NFA<T>::add_transition_epsilon(unsigned from, unsigned to) {
    assert(from < m_states.size() && to < m_states.size()); // state indices must be valid
    m_states[from].epsilon_transitions.insert(to);
}

// Explicit template instantiation
template class NFA<char>;
