#include <finite_automata/print_nfa.hpp>

#include <finite_automata/nfa.hpp>

template<typename T>
void print_nfa(std::ostream& os, NFA<T> const& nfa) {
    if (nfa.has_initial_state()) {
        os << "Initial state: s" << nfa.initial_state().value() << '\n';
    } else {
        os << "No initial state!\n";
    }

    os << "Transitions:\n";
    unsigned num_transitions;
    for (unsigned i = 0; i < nfa.num_states(); i++) {
        for (T symbol : nfa.transition_symbols(i)) {
            for (unsigned dest : nfa.transitions_on(i, symbol)) {
                os << "   from s" << i << " to s" << dest << " on '" << symbol << "'\n";
                num_transitions += 1;
            }
        }
        for (unsigned dest : nfa.epsilon_transitions(i)) {
            os << "   from s" << i << " to s" << dest << " on empty\n";
            num_transitions += 1;
        }
    }

    os << nfa.num_states() << " states, ";
    os << num_transitions << " transitions\n";
}

// Explicit template instantiation
template void print_nfa<char>(std::ostream&, NFA<char> const&);
