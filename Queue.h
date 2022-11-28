// https://github.com/Sajed262
//
//

#ifndef QUEUE
#define QUEUE

#include <iostream>
#include "List.h" // the list in the same repo.

template <class T>
class Queue // FIFO first in first out
{
private:
    /* data */
    List<T> queue;

public:
    Queue() : queue() {}

    ~Queue() = default;

    Queue(const Queue &qu) = default;

    Queue &operator=(const Queue &qu) = default;

    void enqueue(int key, T &data) { queue.addElement(key, data); }

    void dequeue() { queue.removeLast(); }

    bool isEmpty() { return (queue.size == 0) ? true : false; }

    Node<T> *head() { return queue.getLastKey(); }

    int getSize() { return queue.size; }
};

#endif // QUEUE