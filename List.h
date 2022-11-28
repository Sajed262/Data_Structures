// by sajed
//
//

#ifndef HW1_MVNI_L_H
#define HW1_MVNI_L_H

#include "MinHeap.h" // the heap in the same repo
#include <iostream>
#include <vector>

using std::ostream;
using std::vector;

template <class T>
class Node
{
public:
    Node *prev;
    Node *next;
    T data;
    int key;

    Node(Node *p, Node *n, T &d, int k);

    Node(const Node &node);

    ~Node();

    Node &operator=(const Node &node);
};

template <class T>
class List
{
public:
    int size;
    Node<T> *first;
    Node<T> *last;
    Node<T> *Iterator;

    List();

    ~List();

    List(const List &list);

    List &operator=(const List &list);

    void addElement(int key, T &data);

    T *getElement(int key);

    Node<T> *getLastKey();

    Node<T> *getFirstKey();

    Node<T> *getNextKey();

    void removeElement(int key);

    void clearList();

    void removeTop();

    void removeLast();

    List sortList();

    List traverse();
};

template <class T>
Node<T>::Node(Node *p, Node *n, T &d, int k) : prev(p), next(n), data(d),
                                               key(k) {}

template <class T>
Node<T>::Node(const Node &node) = default;

template <class T>
Node<T>::~Node() = default;

template <class T>
Node<T> &Node<T>::operator=(const Node<T> &node) = default;

template <class T>
List<T>::List() : size(0), first(nullptr), last(nullptr), Iterator(nullptr) {}

template <class T>
List<T>::~List()
{
    Node<T> *current = last;
    while (current)
    {
        Node<T> *p = current->prev;
        delete current;
        current = p;
        last = p;
    }
    first = last;
}

template <class T>
List<T>::List(const List<T> &list) : size(list.size)
{
    this->first = this->last = this->Iterator = nullptr;
    Node<T> *current = list.last;
    while (current)
    {
        this->addElement(current->key, current->data);
        current = current->prev;
    }
}

template <class T>
List<T> &List<T>::operator=(const List<T> &list)
{
    if (this == &list)
        return *this;
    Node<T> *current = last;
    while (current)
    {
        Node<T> *p = current->prev;
        delete current;
        current = p;
        last = p;
    }
    first = last;

    this->size = list.size;
    this->first = this->last = this->Iterator = nullptr;
    current = list.last;
    while (current)
    {
        this->addElement(current->key, current->data);
        current = current->prev;
    }
    return *this;
}

template <class T>
void List<T>::addElement(int key, T &data)
{
    Node<T> *n = new Node<T>(nullptr, nullptr, data, key);
    if (first == nullptr)
    {
        first = n;
        last = n;
        size++;
        return;
    }
    first->prev = n;
    n->next = first;
    first = n;
    size++;
    return;
}

template <class T>
T *List<T>::getElement(int key)
{

    Node<T> *current = first;
    while (current)
    {
        if (current->key == key)
            return &(current->data);
        else
            current = current->next;
    }
    return nullptr;
}

template <class T>
void List<T>::removeElement(int key)
{
    Node<T> *current = first;
    while (current)
    {
        if (current->key == key)
        {
            if (current->next)
                current->next->prev = current->prev;
            if (current->prev)
                current->prev->next = current->next;
            if (current == last)
                last = current->prev;
            if (current == first)
                first = current->next;
            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}

template <class T>
Node<T> *List<T>::getLastKey() { return last; }

template <class T>
Node<T> *List<T>::getFirstKey()
{
    if (!first)
        return nullptr;
    Iterator = first;
    return first;
}

template <class T>
Node<T> *List<T>::getNextKey()
{
    if (!Iterator->next)
    {
        Iterator = Iterator->next;
        return nullptr;
    }
    Iterator = Iterator->next;
    return Iterator;
}

template <class T>
void List<T>::clearList()
{
    Node<T> *tmp = getFirstKey();
    while (Iterator)
    {
        getNextKey();
        delete tmp;
    }
    first = last = Iterator = nullptr;
    size = 0;
}

template <class T>
void List<T>::removeTop() // for the stack
{
    Node<T> *top_to_remove = getFirstKey();
    if (top_to_remove->next)
        top_to_remove->next->prev = nullptr;
    first = top_to_remove->next;
    if (!first)
        first = last = Iterator = nullptr;
    delete top_to_remove;
    size--;
}

template <class T>
void List<T>::removeLast() // for the queue
{
    Node<T> *last_to_remove = last;
    if (last_to_remove->prev)
        last_to_remove->prev->next = nullptr;
    last = last_to_remove->prev;
    if (!last)
        first = last = Iterator = nullptr;
    delete last_to_remove;
    size--;
}

// sorting by heap sort O(NlogN)
template <class T>
List<T> List<T>::sortList()
{
    getFirstKey();
    vector<apex<T>> array;

    int i = 0;
    while (Iterator && i < size)
    {
        apex<T> nueva(Iterator->key, Iterator->data);
        array.push_back(nueva);
        i++;
        getNextKey();
    }
    MinHeap<T> heap_sort(array);
    vector<apex<T>> sorted_array = heap_sort.heapSort();
    List<T> sorted;
    for (int i = size - 1; i >= 0; i--)
    {
        sorted.addElement(sorted_array[i].key, sorted_array[i].data);
    }
    return sorted;
}

template <class T>
List<T> List<T>::traverse()
{
    List<T> reversed;
    getFirstKey();
    while (Iterator)
    {
        reversed.addElement(Iterator->key, Iterator->data);
        getNextKey();
    }
    return reversed;
}

#endif // HW1_MVNI_L_H
