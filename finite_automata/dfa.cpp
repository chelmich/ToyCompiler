#include <finite_automata/dfa.hpp>

#include <cassert>

template<typename T>
void DFA<T>::set_initial_state(unsigned state) {
    assert(state < m_states.size()); // state index must be valid
    m_initial_state = state;
}

template<typename T>
std::unordered_map<T, unsigned> DFA<T>::transitions(unsigned state) const {
    assert(state < m_states.size()); // state index must be valid
    return m_states[state].transitions;
}

template<typename T>
unsigned DFA<T>::add_state(bool accepting) {
    const unsigned state = m_states.size();
    m_states.push_back(State(accepting));
    if (accepting) m_accepting_states.insert(state);
    return state;
}

template<typename T>
void DFA<T>::add_transition(unsigned from, unsigned to, T symbol) {
    assert(from < m_states.size() && to < m_states.size()); // state indices must be valid
    assert(!m_states[from].transitions.contains(symbol)); // don't overwrite an existing transition
    m_states[from].transitions[symbol] = to;
}

// Explicit template instantiation
template class DFA<char>;
