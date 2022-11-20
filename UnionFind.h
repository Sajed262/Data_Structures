//
// Created by sajed on 06/06/2021.
//

#ifndef UNTITLED1_UNIONFIND_H
#define UNTITLED1_UNIONFIND_H

#include "AVLTree.h"
#include "RankedAVLTree.h"

class Node {
public:
    int key;
    int num_of_nodes; // nodes that this node is their parent, contains the node itself
    Node *parent;
    RankedAVLTree<int> sells_tree;
    AVLTree<int> cars_tree;

    Node(int key) : key(key), num_of_nodes(1), parent(nullptr) {}

    ~Node() = default;
};

class UnionFind {
    int size;
    Node **array;
    int index;

    static void merge(int *a1, int *a2, int *b1, int *b2, int *c1, int *c2, int l_a, int l_b, int l_c) {
        int ia, ib, ic;
        for (ia = ib = ic = 0; ia < l_a && ib < l_b; ++ic) {
            if (a1[ia] < b1[ib]) {
                c1[ic] = a1[ia];
                c2[ic] = a2[ia++];
            } else if (a1[ia] > b1[ib]) {
                c1[ic] = b1[ib];
                c2[ic] = b2[ib++];
            } else {
                if (a2[ia] < b2[ib]) {
                    c1[ic] = a1[ia];
                    c2[ic] = a2[ia++];
                } else {
                    c1[ic] = b1[ib];
                    c2[ic] = b2[ib++];
                }
            }
        }

        for (; ia < l_a; ia++, ic++) {
            c1[ic] = a1[ia];
            c2[ic] = a2[ia];
        }
        for (; ib < l_b; ib++, ic++) {
            c1[ic] = b1[ib];
            c2[ic] = b2[ib];
        }
    }

    static void FillSellsTree(Node *big, Node *small) {
        int len_small = small->sells_tree.getNumberOfRankedVertexies();
        int len_big = big->sells_tree.getNumberOfRankedVertexies();
        if (len_small == 0 && len_big == 0) return;
        int i = 0;
        int types_small[len_small];
        int sells_small[len_small];
        if (len_small > 0) {
            small->sells_tree.TreeToArrayInOrder(small->sells_tree.getRoot(), types_small, sells_small, i);
            i = 0;
        }
        int types_big[len_big];
        int sells_big[len_big];
        if (len_big > 0) {
            big->sells_tree.TreeToArrayInOrder(big->sells_tree.getRoot(), types_big, sells_big, i);
        }
        int types_merge[len_big + len_small];
        int sells_merge[len_big + len_small];
        merge(sells_small, types_small, sells_big, types_big, sells_merge, types_merge, len_small, len_big,
              len_small + len_big);
        small->sells_tree.clear();
        big->sells_tree.clear();
        big->sells_tree.Fill(types_merge, sells_merge, len_big + len_small);
    }

    static void FillCarsTree(Node *big, Node *small) {
        int len_small = small->cars_tree.getNumOfV();
        int len_big = big->cars_tree.getNumOfV();
        if (len_small == 0 && len_big == 0) return;
        int i = 0;
        int types_small[len_small];
        int sells_small[len_small];
        if (len_small > 0) {
            small->cars_tree.TreeToArrayInOrder(small->cars_tree.getRoot(), types_small, sells_small, i);
            i = 0;
        }
        int types_big[len_big];
        int sells_big[len_big];
        if (len_big > 0) {
            big->cars_tree.TreeToArrayInOrder(big->cars_tree.getRoot(), types_big, sells_big, i);
        }
        int types_merge[len_big + len_small];
        int sells_merge[len_big + len_small];
        merge(types_small, sells_small, types_big, sells_big, types_merge, sells_merge, len_small, len_big,
              len_small + len_big);
        small->cars_tree.clear();
        big->cars_tree.clear();
        big->cars_tree.Fill(types_merge, sells_merge, len_big + len_small);
    }

public:

    UnionFind() {
        size = 2;
        array = new Node *[size];
        for (int i = 0; i < size; ++i) {
            array[i] = nullptr;
        }
        index = 0;
    }

    ~UnionFind() {
        for (int i = 0; i < size; ++i) {
            if (array[i])
                delete array[i];
        }
        delete[]array;
    }

    void add() {
        if (size > index) {
            array[index] = new Node(index);
            index++;
        } else {
            Node **new_arr = new Node *[2 * size];
            for (int i = 0; i < 2 * size; ++i) {
                if (i < size) {
                    new_arr[i] = array[i];
                    array[i] = nullptr;
                } else {
                    new_arr[i] = nullptr;
                }
            }
            delete[]array;
            size = 2 * size;
            array = new_arr;
            array[index] = new Node(index);
            index++;
        }

    }

    Node *Find(int ind) {
        if (ind >= index) return nullptr;
        Node *root = array[ind];
        while (root->parent != nullptr)
            root = root->parent;

        Node *tmp = array[ind];
        while (tmp->parent && tmp->parent != root) {
            Node *p = tmp->parent;
            tmp->parent = root;
            tmp = p;
        }
        return root;
    }

    void sell(int agencyId, int typeId, int k) {
        Node *root = Find(agencyId);
        if (root->cars_tree.find(typeId)) {
            int x = *(root->cars_tree.getData(typeId));
            root->cars_tree.remove(typeId);
            root->sells_tree.remove(typeId, x);
            k += x;
            root->cars_tree.insert(typeId, k);
            root->sells_tree.insert(typeId, k);
        } else {
            root->cars_tree.insert(typeId, k);
            root->sells_tree.insert(typeId, k);
        }
    }

    void Union(int idx1, int idx2) {
        Node *root1 = Find(idx1);
        Node *root2 = Find(idx2);
        if (root2 == root1)
            return;
        Node *big;
        Node *small;
        if (root1->num_of_nodes >= root2->num_of_nodes) {
            big = root1;
            small = root2;
        } else {
            big = root2;
            small = root1;
        }
        small->parent = big;
        big->num_of_nodes += small->num_of_nodes;
        FillCarsTree(big, small);
        FillSellsTree(big, small);
    }

};

#endif //UNTITLED1_UNIONFIND_H
