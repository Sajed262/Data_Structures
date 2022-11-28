// by sajed
//
//

#ifndef MIN_HEAP
#define MIN_HEAP

#include <iostream>
#include <vector>

using std::vector;

template<class T>
class apex {
public:
    int key;
    T data;

    apex(int k, T &d) : key(k), data(d) {}

    ~apex() = default;

    apex(const apex &ap) = default;

    apex &operator=(const apex &ap) = default;

};

template<class T>
class MinHeap {
    vector<apex<T>> heap;

    void replace(int i, int son) {
        int tmp = heap[i - 1].key;
        heap[i - 1].key = heap[son - 1].key;
        heap[son - 1].key = tmp;

        T tmp2 = heap[i - 1].data;
        heap[i -1].data = heap[son-1].data;
        heap[son-1].data = tmp2;
    }

    void siftDown(int i) {
        int left_son = 2 * i;
        int right_son = 2 * i + 1;
        if (left_son > (int)heap.size())
            return;
        if (right_son > (int)heap.size() && heap[i - 1].key <= heap[left_son - 1].key)
            return;
        if (right_son > (int)heap.size() && heap[i - 1].key > heap[left_son - 1].key) {
            replace(i, left_son);
            return siftDown(left_son);
        }
        // replace between i and the left son
        if (heap[left_son - 1].key < heap[right_son - 1].key && (heap[i - 1].key > heap[right_son - 1].key ||
                                                                   heap[i - 1].key > heap[left_son - 1].key)) {
            replace(i, left_son);
            return siftDown(left_son);
        } else if (heap[left_son - 1].key > heap[right_son - 1].key && (heap[i - 1].key > heap[right_son - 1].key ||
                                                                          heap[i - 1].key > heap[left_son - 1].key)) {
            replace(i, right_son); // replace between i and the right son
            return siftDown(right_son);
        }
    }

    void siftUp(int i) {
        int parent = i/2;
        if (parent == 0 || (heap[i - 1].key >= heap[parent - 1].key)) return;
        replace(i,parent);
        siftUp(parent);
    }

public:
    MinHeap() : heap() {}

    MinHeap(vector<apex<T>> vec) : heap(vec) { // making the heap from n elements takes O(n)
        int start = heap.size() / 2;
        while (start > 0) {
            siftDown(start);
            start--;
        }
    }

    ~MinHeap() = default;

    MinHeap(const MinHeap &min) = default;

    MinHeap &operator=(const MinHeap &min) = default;

    int getSize() { return heap.size(); }

    apex<T> min() { return heap[0]; }

    apex<T> deleteMin() {
        apex<T> min(heap[0].key,heap[0].data);
        replace(1,heap.size());
        heap.pop_back();
        siftDown(1);
        return min;
    }

    void insert(int key, T &data) {
        apex<T> nueva(key,data);
        heap.push_back(nueva);
        siftUp(heap.size());
    }

    void decreaseKey(int key_to_decrease,int new_key) {
        if (key_to_decrease <= new_key) return;
        for (int i = 0; i < heap.size(); ++i) {
            if (heap[i].key == key_to_decrease) {
                heap[i].key = new_key;
                siftUp(i+1);
                return;
            }
        }
    }

    vector<apex<T>> heapSort() {
        vector<apex<T>> sorted;
        for (int i = 0; i < (int)heap.size();) {
            apex<T> min = deleteMin();
            sorted.push_back(min);
        }
        return sorted;
    }

};


#endif //MIN_HEAP