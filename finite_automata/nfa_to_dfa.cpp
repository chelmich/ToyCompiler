#include <finite_automata/nfa_to_dfa.hpp>

#include <finite_automata/dfa.hpp>
#include <finite_automata/nfa.hpp>

#include <cassert>
#include <iostream> // for debug

template<typename T>
bool set_accepts(NFA<T> const& nfa, std::unordered_set<unsigned> states) {
    for (unsigned state : states) {
        if (nfa.accepting_states().contains(state)) {
            return true;
        }
    }

    return false;
}

template<typename T>
DFA<T> nfa_to_dfa(NFA<T> const& nfa) {
    assert(nfa.has_initial_state());

    DFA<T> dfa;

    std::unordered_set<unsigned> initial_subset = nfa.epsilon_closure({nfa.initial_state().value()});
    const unsigned initial_dfa_state = dfa.add_state(set_accepts(nfa, initial_subset));
    dfa.set_initial_state(initial_dfa_state);

    // FIXME: ideally use a multimap here, need hash function for unordered_set
    std::unordered_map<unsigned, std::unordered_set<unsigned>> conversion_table;
    conversion_table[initial_dfa_state] = initial_subset;

    // Begin with initial DFA state on the work list
    std::vector<unsigned> work_list = {initial_dfa_state};

    while (!work_list.empty()) {
        const unsigned current_dfa_state = work_list.back();
        work_list.pop_back();

        std::unordered_set<unsigned> const& current_nfa_states = conversion_table.at(current_dfa_state);

        // Build map from transition symbols to sets of NFA states
        std::unordered_map<T, std::unordered_set<unsigned>> transition_map;
        for (unsigned nfa_state : current_nfa_states) {
            for (T symbol : nfa.transition_symbols(nfa_state)) {
                std::unordered_set<unsigned> const& destinations = nfa.transitions_on(nfa_state, symbol);
                transition_map[symbol].insert(destinations.begin(), destinations.end());
            }
        }

        for (auto& [symbol, subset] : transition_map) {
            // Expand set of NFA states by epsilon transitions
            subset = nfa.epsilon_closure(subset);

            // Search the conversion table for a matching set of NFA states
            bool found_match = false;
            unsigned matched_dfa_state;
            for (auto [key, value] : conversion_table) {
                if (value == subset) {
                    found_match = true;
                    matched_dfa_state = key;
                    break;
                }
            }

            if (found_match) {
                dfa.add_transition(current_dfa_state, matched_dfa_state, symbol);
            } else {
                unsigned new_dfa_state = dfa.add_state(set_accepts(nfa, subset));
                conversion_table[new_dfa_state] = subset;
                dfa.add_transition(current_dfa_state, new_dfa_state, symbol);

                // Add new state to the work list
                work_list.push_back(new_dfa_state);
            }
        }
    }

    // Dump conversion table for debug
    /*
    for (auto [dfa_state, nfa_states] : conversion_table) {
        std::cout << "s" << dfa_state << "' ->";
        for (unsigned state : nfa_states) {
            std::cout << " s" << state;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    */

    return dfa;
}

// Explicit template instantiation
template DFA<char> nfa_to_dfa<char>(NFA<char> const&);
