#include <regex/expr_to_nfa.hpp>

#include <finite_automata/nfa.hpp>

#include <regex/expr.hpp>

#include <cassert>
#include <vector>

NFA<char> expr_to_nfa(RE::Expr const* regex) {
    assert(regex != nullptr);

    NFA<char> nfa;

    // Create start and end states
    const unsigned state_initial = nfa.add_state();
    const unsigned state_final = nfa.add_state(true);
    nfa.set_initial_state(state_initial);

    // Represents a fragment of NFA left to convert
    struct Fragment {
        unsigned from;
        unsigned to;
        RE::Expr const* expr;
    };

    // Start the stack with the initial fragment being the whole expression
    std::vector<Fragment> stack = {{state_initial, state_final, regex}};

    while (!stack.empty()) {
        // Pop a fragment from the stack
        Fragment frag = stack.back();
        stack.pop_back();

        using Type = RE::Expr::Type;
        switch (frag.expr->type()) {
        case Type::Epsilon:
            nfa.add_transition_epsilon(frag.from, frag.to);
            break;
        case Type::Literal:
            nfa.add_transition(frag.from, frag.to, frag.expr->literal());
            break;
        case Type::Star:
            nfa.add_transition_epsilon(frag.from, frag.to);
            stack.push_back({frag.from, frag.from, frag.expr->sub()});
            break;
        case Type::And: {
            unsigned new_state = nfa.add_state();
            stack.push_back({frag.from, new_state, frag.expr->left()});
            stack.push_back({new_state, frag.to, frag.expr->right()});
            break;
        }
        case Type::Or:
            stack.push_back({frag.from, frag.to, frag.expr->left()});
            stack.push_back({frag.from, frag.to, frag.expr->right()});
            break;
        }
    }

    return nfa;
}
