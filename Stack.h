// https://github.com/Sajed262
//
//

// the optimal implementation of stack uses list and arrays, the main data structure is the list
// so that each Node contaians an array
#ifndef STACK
#define STACK

#include <iostream>
#include "List.h" // the list in the same repo.

template <class T>
class Stack // LIFO Last In First Out
{
private:
    /* data */
    List<T> stack;

public:
    Stack() : stack() {}

    ~Stack() = default;

    Stack(const Stack &st) = default;

    Stack &operator=(const Stack &st) = default;

    void push(int key, T &data) { stack.addElement(key, data); }

    void pop() { stack.removeTop(); }

    Node<T> *top() { return stack.getFirstKey(); }

    bool isEmpty() { return (stack.size == 0) ? true : false; }

    int getSize() { return stack.size; }
};

#endif // STACK