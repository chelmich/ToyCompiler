#include <finite_automata/print_nfa.hpp>

#include <finite_automata/nfa.hpp>

template<typename T>
void print_nfa(std::ostream& os, NFA<T> const& nfa) {
    if (nfa.has_initial_state()) {
        os << "Initial state: s" << nfa.initial_state().value() << '\n';
    } else {
        os << "No initial state!\n";
    }

    std::unordered_set<unsigned> const& accepting_states = nfa.accepting_states();
    if (accepting_states.empty()) {
        os << "No accepting states!\n";
    } else if (accepting_states.size() == 1) {
        os << "Accepting state: s" << *accepting_states.begin() << '\n';
    } else {
        os << "Accepting states:";
        for (auto it = accepting_states.begin(); it != accepting_states.end(); it++) {
            os << " s" << *it;
            if (std::next(it) != accepting_states.end()) {
                os << ',';
            }
        }
        os << '\n';
    }

    os << "Transitions:\n";
    unsigned num_transitions = 0;
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

    os << nfa.num_states() << " states (" << accepting_states.size() << " accepting), ";
    os << num_transitions << " transitions\n";
}

template<typename T>
void print_nfa_graphviz(std::ostream& os, NFA<T> const& nfa) {
    os << "digraph NFA {\n";
    os << "rankdir = LR;\n";
    os << "edge [arrowhead=empty];\n";

    // Start state arrow
    if (nfa.has_initial_state()) {
        os << "start -> s" << nfa.initial_state().value() << " [style=bold];\n";
    }

    // Epsilon transitions
    for (unsigned i = 0; i < nfa.num_states(); i++) {
        for (unsigned dest : nfa.epsilon_transitions(i)) {
            os << "s" << i << " -> s" << dest;
            os << " [style=dashed];\n";
        }
    }

    // Symbol transitions
    for (unsigned i = 0; i < nfa.num_states(); i++) {
        for (T symbol : nfa.transition_symbols(i)) {
            for (unsigned dest : nfa.transitions_on(i, symbol)) {
                os << "s" << i << " -> s" << dest;
                os << " [label=\"" << symbol << "\" weight=50];\n";
            }
        }
    }

    // Hidden start node
    if (nfa.has_initial_state()) {
        os << "start [shape=none label=\"\"]\n";
    }

    // State nodes
    std::unordered_set<unsigned> const& accepting_states = nfa.accepting_states();
    for (size_t i = 0; i < nfa.num_states(); i++) {
        os << 's' << i << " [shape=";
        if (accepting_states.contains(i)) {
            os << "doublecircle";
        } else {
            os << "circle";
        }
        os << "];\n";
    }

    os << "}\n";
}

// Explicit template instantiation
template void print_nfa<char>(std::ostream&, NFA<char> const&);
template void print_nfa_graphviz<char>(std::ostream&, NFA<char> const&);
