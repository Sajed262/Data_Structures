// by sajed
//
//

// there is no insert function, the purpose of the heap is for sorting only, O(NlogN).
//
//
// you can modify it for insertion but then you cant use array, because the size of is not dynamic, and if it is dynamic it will cost alot.
#ifndef MAX_HEAP
#define MAX_HEAP

#include <iostream>
template <class T>
class Unit
{
public:
    int key;
    T *data;

    Unit(int key, T &d) : key(key), data(new T(d)) {}

    ~Unit()
    {
        delete data;
    }

    Unit(const Unit &un)
    {
        key = un.key;
        data = new T(un.data);
    }
};

template <class T>
class MaxHeap // initialized with n elements
{
    /* data */
    int size;
    Unit<T> **data;

    static void replace(Unit<T> **arr, int i, int son)
    {
        int tmp = arr[i - 1]->key;
        arr[i - 1]->key = arr[son - 1]->key;
        arr[son - 1]->key = tmp;

        T tmp2 = *(arr[i - 1]->data);
        *(arr[i - 1]->data) = *(arr[son - 1]->data);
        *(arr[son - 1]->data) = tmp2;
    }

    static void siftDown(Unit<T> **arr, int i, int size)
    {
        int parent = i / 2;
        int left_son = 2 * i;
        int right_son = 2 * i + 1;
        if (left_son > size)
            return;
        if (right_son > size && arr[i - 1]->key > arr[left_son - 1]->key)
            return;
        if (right_son > size && arr[i - 1]->key < arr[left_son - 1]->key)
        {
            replace(arr, i, left_son);
            return siftDown(arr, left_son, size);
        }

        if (arr[left_son - 1]->key > arr[right_son - 1]->key && (arr[i - 1]->key < arr[right_son - 1]->key || arr[i - 1]->key < arr[left_son - 1]->key)) // replace between i and the left son
        {
            replace(arr, i, left_son);
            return siftDown(arr, left_son, size);
        }
        else if (arr[left_son - 1]->key < arr[right_son - 1]->key && (arr[i - 1]->key < arr[right_son - 1]->key || arr[i - 1]->key < arr[left_son - 1]->key))
        { // replace between i and the right son
            replace(arr, i, right_son);
            return siftDown(arr, right_son, size);
        }
    }

    Unit<T> *deleteMax()
    {
        Unit<T> *max = new Unit<T>(data[0]->key, *data[0]->data);
        replace(data, 1, size);
        delete data[size - 1];
        data[size - 1] = nullptr;
        size--;
        siftDown(data, 1, size);
        return max;
    }

public:
    // array can be a complete binary tree,
    // when the parent of i'th vertex is at index i/2 floor, left son at 2i, right son 2i+1
    // the complexity of making a heap of n elements is O(n)
    MaxHeap(int n, T arr[], int array[]) : size(n), data(new Unit<T> *[size])
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = new Unit<T>(array[i], arr[i]);
        }

        int start = size / 2;
        while (start > 0)
        {
            siftDown(data, start, size);
            start--;
        }
    }

    ~MaxHeap()
    {
        for (size_t i = 0; i < size; i++)
        {
            delete data[i];
        }
        delete data;
    }

    Unit<T> *max() { return data[0]; }

    Unit<T> **heapSort()
    {
        Unit<T> **sorted = new Unit<T> *[size];
        for (int i = size - 1; i >= 0; i--)
        {
            sorted[i] = deleteMax();
        }
        return sorted;
    }
};

#endif // MAX_HEAP