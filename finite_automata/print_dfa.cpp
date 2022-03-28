#include <finite_automata/print_dfa.hpp>

#include <finite_automata/dfa.hpp>

template<typename T>
void print_dfa(std::ostream& os, DFA<T> const& dfa) {
    if (dfa.has_initial_state()) {
        os << "Initial state: s" << dfa.initial_state().value() << '\n';
    } else {
        os << "No initial state!\n";
    }

    const std::unordered_set<unsigned> accepting_states = dfa.accepting_states();
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
    for (unsigned i = 0; i < dfa.num_states(); i++) {
        for (auto const& [symbol, dest] : dfa.transitions(i)) {
            os << "   from s" << i << " to s" << dest << " on '" << symbol << "'\n";
            num_transitions += 1;
        }
    }

    os << dfa.num_states() << " states (" << accepting_states.size() << " accepting), ";
    os << num_transitions << " transitions\n";
}

template<typename T>
void print_dfa_graphviz(std::ostream& os, DFA<T> const& dfa) {
    os << "digraph DFA {\n";
    os << "rankdir = LR;\n";
    os << "edge [arrowhead=empty];\n";

    // Start state arrow
    if (dfa.has_initial_state()) {
        os << "start -> s" << dfa.initial_state().value() << " [style=bold];\n";
    }

    // Transitions
    for (unsigned i = 0; i < dfa.num_states(); i++) {
        for (auto const& [symbol, dest] : dfa.transitions(i)) {
            os << "s" << i << " -> s" << dest;
            os << " [label=\"" << symbol << "\" weight=50];\n";
        }
    }

    // Hidden start node
    if (dfa.has_initial_state()) {
        os << "start [shape=none label=\"\"]\n";
    }

    // State nodes
    std::unordered_set<unsigned> accepting_states = dfa.accepting_states();
    for (size_t i = 0; i < dfa.num_states(); i++) {
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
template void print_dfa<char>(std::ostream&, DFA<char> const&);
template void print_dfa_graphviz<char>(std::ostream&, DFA<char> const&);
