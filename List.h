// by sajed
//
//

#ifndef HW1_MVNI_L_H
#define HW1_MVNI_L_H

#include "MaxSortHeap.h" // the heap in the same repo
#include <ostream>

using std::ostream;

template <class T>
class Node
{
public:
    Node *prev;
    Node *next;
    T *data;
    int key;

    Node(Node *p, Node *n, T &d, int k);

    Node(const Node &node);

    ~Node();

    void clearNode();
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

    void addElement(int key, T &data);

    T *getElement(int key);

    Node<T> *getFirstKey();

    Node<T> *getNextKey();

    void removeElement(int key);

    void clearList();

    List &sortedList();

    List &traverse();
};

template <class T>
Node<T>::Node(Node *p, Node *n, T &d, int k) : prev(p), next(n), data(new T(d)),
                                               key(k) {}

template <class T>
Node<T>::Node(const Node &node)
{
    this->key = node.key;
    this->data = new T(*node.data);
    this->next = node.next;
    this->prev = node.prev;
}

template <class T>
Node<T>::~Node()
{
    delete data;
    data = nullptr;
}

template <class T>
void Node<T>::clearNode()
{
    delete data;
    data = nullptr;
}

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
void List<T>::addElement(int key, T &data)
{
    if (this->getElement(key))
        return;

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
            return (current->data);
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
    getFirstKey();
    while (Iterator)
    {
        Iterator->clearNode();
        getNextKey();
    }
    first = last = Iterator = nullptr;
    size = 0;
}

// heap for the sort
template <class T>
List<T> &List<T>::sortedList()
{
    getFirstKey();
    int array[size];
    T arr[size];
    int i = 0;
    while (Iterator && i < size)
    {
        array[i] = Iterator->key;
        arr[i] = *Iterator->data;
        i++;
        getNextKey();
    }
    MaxSortHeap<T> heap_sort(size, arr, array);
    Unit<T> **sorted_array = heap_sort.heapSort();
    List<T> *sorted = new List<T>();
    for (int i = size - 1; i >= 0; i--)
    {
        sorted->addElement(sorted_array[i]->key, *sorted_array[i]->data);
    }

    return *sorted;
}

template <class T>
List<T> &List<T>::traverse()
{
    List<T> *reversed = new List<T>();
    getFirstKey();
    while (Iterator)
    {
        reversed->addElement(Iterator->key, *Iterator->data);
        getNextKey();
    }
    return *reversed;
}

#endif // HW1_MVNI_L_H
