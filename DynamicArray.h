// https://github.com/Sajed262
//
//

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include <vector>
#include <iostream>
#include <assert.h>

using std::vector;

template <class T>
class DynamicArray
{
private:
    /* data */
    int size;
    int top; // the top is the first unused index in the array.
    T *dynamic_array;

public:
    DynamicArray() : size(2), top(0), dynamic_array(new T[size]) {}

    DynamicArray(vector<T> &vec) : size(2 * vec.size()), top(0), dynamic_array(new T[2 * size])
    {
        for (; top < vec.size(); top++)
            dynamic_array[top] = vec[top];
    }

    ~DynamicArray()
    {
        delete[] dynamic_array;
    }

    DynamicArray(const DynamicArray &dy)
    {
        size = dy.size;
        dynamic_array = new T[size];
        for (top = 0; top < dy.top; top++)
        {
            dynamic_array[top] = dy.dynamic_array[top];
        }
    }

    DynamicArray &operator=(const DynamicArray &dy)
    {
        if (this == &dy)
            return *this;       // checking for self-assignment
        delete[] dynamic_array; // delete old data;
        size = dy.size;
        dynamic_array = new T[size];       // allocating the new data;
        for (top = 0; top < dy.top; top++) // transfer the data
        {
            /* code */
            dynamic_array[top] = dy.dynamic_array[top];
        }
        return *this;
    }

    bool isEmpty() { return (top == 0) ? true : false; }

    int getSize() { return size; }

    int getTop() { return top; }

    void insert(T &data)
    {
        if (size > top)
            dynamic_array[top++] = data;
        else
        {
            T *new_arr = new T[size * 2];
            for (int i = 0; i < top; ++i)
                new_arr[i] = dynamic_array[i];
            delete[] dynamic_array;
            size = 2 * size;
            dynamic_array = new_arr;
            dynamic_array[top++] = data;
        }
    }

    void remove(int index)
    {
        if (index >= top)
            return;
        for (int i = index; i < top; i++)// when removing not from the end we need to shift the other elements
            dynamic_array[i] = dynamic_array[i + 1];
        top--;
        if (top <= size / 4)
        {
            T *new_arr = new T[size / 2];
            for (int i = 0; i < top; ++i)
                new_arr[i] = dynamic_array[i];
            delete[] dynamic_array;
            size = size / 2;
            dynamic_array = new_arr;
        }
    }

    T operator[](int index)
    {
        assert(index < top);
        assert(index >= 0);
        return dynamic_array[index];
    }
};

#endif // DYNAMIC_ARRAY