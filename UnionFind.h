// https://github.com/Sajed262
//
//


// the implementation uses union by size and path compression optimization.
// so that the union and find functions amortized complexity is O(log*N) "log star N".
// log*N is the number of times the logarithm function must be iteratively applied before the result is less than or equal to 1.
#ifndef UNION_FIND
#define UNION_FIND

#include "DynamicArray.h"
#include <vector>

using std::vector;

template <class T>
class Unit
{
public:
    int key;
    int num_of_nodes; // nodes that this node is their parent, contains the node itself
    T data;
    Unit *parent;

    Unit(int key, T &data) : key(key), num_of_nodes(1), data(data), parent(nullptr) {}

    ~Unit() = default;

    Unit(const Unit &un) = default;

    Unit &operator=(const Unit &un) = default;
};

template <class T>
class UnionFind
{
private:
    /* data */
    DynamicArray<Unit<T>> array;

public:
    UnionFind() : array() {}

    UnionFind(vector<T> &vec) : array(vec) {}

    ~UnionFind() = default;

    UnionFind(const UnionFind &un) = default;

    UnionFind &operator=(const UnionFind &un) = default;

    void insert(int key, T& data) {
        Unit<T> new_(key,data);
        array.insert(new_);
    }

    Unit<T> *Find(int index) 
    {
        if(index >= array.getTop()) return nullptr;
        Unit<T> *root = array[index];
        while (root->parent)
            root = root->parent;
        Unit<T> *tmp = array[index];
        while (tmp->parent && tmp->parent != root) // Path compression optimization
        {
            Unit<T> *p = tmp->parent;
            p->num_of_nodes -= tmp->num_of_nodes;

            tmp->parent = root;
            tmp = p;
        }
        return root;
    }

    void Union(int index1, int index2) 
    {
        Unit<T> *root1 = Find(index1);
        Unit<T> *root2 = Find(index2);
        if (root1 == root2)
            return;
        Unit<T> *big = (root1->num_of_nodes >= root2->num_of_nodes) ? root1 : root2;
        Unit<T> *small = (big == root1) ? root2 : root1;
        small->parent = big; // union by size
        big->num_of_nodes += small->num_of_nodes;   
    }

};

#endif // UNION_FIND