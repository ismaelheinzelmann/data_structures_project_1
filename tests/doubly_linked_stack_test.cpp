#include <cassert>
#include "../data_structures/linked_stack.h"

int main() {
    structures::LinkedStack<int> stack;

    // Test pushing elements onto the stack
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(stack.size() == 3);

    // Test popping elements from the stack
    assert(stack.pop() == 3);
    assert(stack.pop() == 2);
    assert(stack.size() == 1);

    // Test checking the top element of the stack
    assert(stack.top() == 1);

    // Test clearing the stack
    stack.clear();
    assert(stack.empty());

    return 0;
}
