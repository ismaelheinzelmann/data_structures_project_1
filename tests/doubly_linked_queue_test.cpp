#include <iostream>
#include <cassert>
#include "doubly_linked_queue.h"
using namespace std;

void test_linked_queue() {
    structures::LinkedQueue<int> queue;

    // test empty
    assert(queue.empty());

    // test enqueue
    queue.enqueue(1);
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.front() == 1);
    assert(queue.back() == 1);

    queue.enqueue(2);
    assert(queue.size() == 2);
    assert(queue.front() == 1);
    assert(queue.back() == 2);

    queue.enqueue(3);
    assert(queue.size() == 3);
    assert(queue.front() == 1);
    assert(queue.back() == 3);

    queue.enqueue(4);
    assert(queue.size() == 4);
    assert(queue.front() == 1);
    assert(queue.back() == 4);

    // test dequeue
    assert(queue.dequeue() == 1);
    assert(queue.size() == 3);
    assert(queue.front() == 2);
    assert(queue.back() == 4);

    assert(queue.dequeue() == 2);
    assert(queue.size() == 2);
    assert(queue.front() == 3);
    assert(queue.back() == 4);

    assert(queue.dequeue() == 3);
    assert(queue.size() == 1);
    assert(queue.front() == 4);
    assert(queue.back() == 4);

    assert(queue.dequeue() == 4);
    assert(queue.size() == 0);
    assert(queue.empty());

    // test clear
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.clear();
    assert(queue.empty());
    assert(queue.size() == 0);
    cout<<"All tests passed!"<<endl;
}

int main() {
    test_linked_queue();
    return 0;
}
