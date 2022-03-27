#include <finite_automata/nfa.hpp>

#include <cassert>

template<typename T>
void NFA<T>::set_initial_state(unsigned state) {
    assert(state < m_states.size());
    m_initial_state = state;
}

template<typename T>
unsigned NFA<T>::add_state() {
    m_states.push_back(State());
    return m_states.size() - 1;
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
