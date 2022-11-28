// https://github.com/Sajed262
//
//

#ifndef UNTITLED1_RankedAVLTree_H
#define UNTITLED1_RankedAVLTree_H

#include <iostream>


template<class T>
class RankedVertex {
public:
    T *data;
    int key;
    int height;
    int i;

    class RankedVertex *left;

    class RankedVertex *right;

    class RankedVertex *parent;

    RankedVertex() {}

    RankedVertex(T &data, int key, int height);

    RankedVertex(const RankedVertex &other);

    RankedVertex &operator=(const RankedVertex<T> &other);

    ~RankedVertex();
};

template<class T>
RankedVertex<T>::RankedVertex(T &data, int key, int height) : data(new T(data)), key(key),
                                                              height(height), i(1), left(NULL),
                                                              right(NULL), parent(NULL) {
}

template<class T>
RankedVertex<T>::RankedVertex(const RankedVertex<T> &other) {
    this->key = other.key;
    this->i = other.i;
    this->height = other.height;
    if (this->data)
        delete this->data;
    this->data = new T(*other.data);
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

template<class T>
RankedVertex<T> &RankedVertex<T>::operator=(const RankedVertex<T> &other) {
    this->key = other.key;
    this->i = other.i;
    this->height = other.height;
    if (this->data)
        delete this->data;
    this->data = (new T(*other.data));
    return *this;
}

template<class T>
RankedVertex<T>::~RankedVertex<T>() {
    delete data;
}
///////////////////////////////////////////

template<class T>
class RankedAVLTree {
    RankedVertex<T> *root;
    int number_of_vertexs;

    static void deleteTree(RankedVertex<T> *root);

    static RankedVertex<T> *copyAux(RankedVertex<T> *root1, RankedVertex<T> *root2);

    static bool compareByKeys(int key1, int key2, T &data1, T &data2);

    static bool checkIfContains(RankedVertex<T> *root, int key, T &data);

    static void updateHeight(RankedVertex<T> *vertex);

    static RankedVertex<T> *rotateRight(RankedVertex<T> *vertex1, RankedVertex<T> *vertex2);

    static RankedVertex<T> *rotateLeft(RankedVertex<T> *vertex1, RankedVertex<T> *vertex2);

    static void updatei(RankedVertex<T> *vertex);

    static RankedVertex<T> *leftLeftCase(RankedVertex<T> *vertex);

    static RankedVertex<T> *rightRightCase(RankedVertex<T> *vertex);

    static RankedVertex<T> *rightLeftCase(RankedVertex<T> *vertex);

    static RankedVertex<T> *leftRightCase(RankedVertex<T> *vertex);

    static RankedVertex<T> *balanceTree(RankedVertex<T> *vertex);

    static bool checkIfBalanced(RankedVertex<T> *vertex);

    static RankedVertex<T> *insertAux(RankedVertex<T> *vertex, int key, T &data);

    static T *getDataAux(RankedVertex<T> *vertex, int key, T &data);

    static RankedVertex<T> *findSuccessor(RankedVertex<T> *vertex);

    static RankedVertex<T> *removeAux(RankedVertex<T> *vertex, int key, T &data);

    static RankedVertex<T> *getVAux(RankedVertex<T> *vertex, int key, T &data);

    static RankedVertex<T> *FillAux(RankedVertex<T> *v, int *array1, int *array2, int size, RankedVertex<T> *p, int h) {
        if (size <= 0) return nullptr;
        int mid = size / 2;
        v = new RankedVertex<T>(array2[mid], array1[mid], h);
        v->parent = p;
        v->i = size;
        v->left = FillAux(v->left, array1, array2, mid, v, h + 1);
        v->right = FillAux(v->right, array1 + mid + 1, array2 + mid + 1, size - mid - 1, v, h + 1);
        return v;
    }

    static void ithAux(RankedVertex<T> *v, int i, int *res) {
        int i_left = v->left == nullptr ? 0 : (v->left)->i;
        if (i_left == i) {
            *res = v->key;
        } else if (i_left < i) ithAux(v->right, (i - 1 - i_left), res);
        else ithAux(v->left, i, res);
    }

public:

    RankedAVLTree();

    RankedAVLTree(const RankedAVLTree &other);

    RankedAVLTree &operator=(const RankedAVLTree &tree) = default;

    ~RankedAVLTree();

    void insert(int key, T &data);

    int getRankedAVLTreeHeight() const;

    T *getData(int key, T &data) const;

    bool find(int key, T &data) const;

    RankedVertex<T> *getV(int key, T &data);

    void remove(int key, T &data);

    void clear();

    int getNumberOfRankedVertexies() {
        return number_of_vertexs;
    }

    RankedVertex<T> *getRoot() {
        if (root)
            return root;
        return nullptr;
    }

    void TreeToArrayInOrder(RankedVertex<int> *v, int *array1, int *array2, int &i) {
        if (!v)
            return;
        TreeToArrayInOrder(v->left, array1, array2, i);
        array1[i] = v->key;
        array2[i++] = *v->data;
        TreeToArrayInOrder(v->right, array1, array2, i);
    }

    void Fill(int *arr1, int *arr2, int size) {
        root = FillAux(root, arr1, arr2, size, nullptr, 0);
        number_of_vertexs = size;
    }

    void ith(int i, int *res) {
        ithAux(root,i,res);
    }

};

template<class T>
RankedAVLTree<T>::RankedAVLTree() : root(NULL), number_of_vertexs(0) {}

template<class T>
RankedAVLTree<T>::RankedAVLTree(const RankedAVLTree &other): root(NULL), number_of_vertexs(0) {
    root = copyAux(root, other.root);
    number_of_vertexs = other.number_of_vertexs;

}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::copyAux(RankedVertex<T> *root1, RankedVertex<T> *root2) {
    if (!root2)
        return root1;
    root1 = new RankedVertex<T>(*(root2->data), root2->key, root2->height);
    root1->left = copyAux(root1->left, root2->left);
    if (root1->left)
        root1->left->parent = root1;
    root1->right = copyAux(root1->right, root2->right);
    if (root1->right)
        root1->right->parent = root1;
    return root1;
}

template<class T>
void RankedAVLTree<T>::deleteTree(RankedVertex<T> *root) {
    if (!root)
        return;
    if (root->left)
        deleteTree(root->left);
    if (root->right)
        deleteTree(root->right);
    delete root;

}

template<class T>
void RankedAVLTree<T>::clear() {
    deleteTree(root);
    root = NULL;
    number_of_vertexs = 0;
}

template<class T>
RankedAVLTree<T>::~RankedAVLTree() {
    clear();
}

template<class T>
bool RankedAVLTree<T>::compareByKeys(int key1, int key2, T &data1, T &data2) {

    if (data2 > data1) return true;
    else if (data2 < data1) return false;
    else {
        if (key2 > key1) return true;
        else if (key2 < key1) return false;
    }
    return false;
}

template<class T>
bool RankedAVLTree<T>::checkIfContains(RankedVertex<T> *root, int key, T &data) {
    if (!root)
        return false;
    if (root && root->key == key && *root->data == data)
        return true;
    if (compareByKeys(key, root->key, data, *root->data))
        return checkIfContains(root->left, key, data);
    else
        return checkIfContains(root->right, key, data);
}

template<class T>
void RankedAVLTree<T>::updateHeight(RankedVertex<T> *vertex) {
    if (!vertex)
        return;
    int left = vertex->left == NULL ? -1 : (vertex->left)->height;
    int right = vertex->right == NULL ? -1 : (vertex->right)->height;
    vertex->height = left > right ? left + 1 : right + 1;
    return;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::rotateRight(RankedVertex<T> *vertex1, RankedVertex<T> *vertex2) {
    if (!vertex2->parent) {
        vertex1 = vertex2->left;
        vertex2->left = (vertex2->left)->right;
        vertex1->right = vertex2;
        vertex2->parent = vertex1;
        if (vertex2->left)
            (vertex2->left)->parent = vertex2;
        return vertex1;
    } else {
        vertex1 = vertex2->left;
        vertex2->left = (vertex2->left)->right;
        vertex1->right = vertex2;
        vertex1->parent = vertex2->parent;
        vertex2->parent = vertex1;
        if (vertex2->left)
            (vertex2->left)->parent = vertex2;
        return vertex1;
    }
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::rotateLeft(RankedVertex<T> *vertex1, RankedVertex<T> *vertex2) {
    if (!vertex2->parent) {
        vertex1 = vertex2->right;
        vertex2->right = (vertex2->right)->left;
        vertex1->left = vertex2;
        vertex2->parent = vertex1;
        if (vertex2->right)
            (vertex2->right)->parent = vertex2;
        return vertex1;
    } else {
        vertex1 = vertex2->right;
        vertex2->right = (vertex2->right)->left;
        vertex1->left = vertex2;
        vertex1->parent = vertex2->parent;
        vertex2->parent = vertex1;
        if (vertex2->right)
            (vertex2->right)->parent = vertex2;
        return vertex1;
    }

}

template<class T>
void RankedAVLTree<T>::updatei(RankedVertex<T> *vertex) {
    int i_left = vertex->left == NULL ? 0 : (vertex->left)->i;
    int i_right = vertex->right == NULL ? 0 : (vertex->right)->i;
    vertex->i = i_left + i_right + 1;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::leftLeftCase(RankedVertex<T> *vertex) {
    RankedVertex<T> *tmp = NULL;
    tmp = rotateRight(tmp, vertex);
    updateHeight(vertex);
    updateHeight(tmp);
    updatei(vertex);
    updatei(tmp);
    return tmp;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::rightRightCase(RankedVertex<T> *vertex) {
    RankedVertex<T> *tmp = NULL;
    tmp = rotateLeft(tmp, vertex);
    updateHeight(vertex);
    updateHeight(tmp);
    updatei(vertex);
    updatei(tmp);
    return tmp;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::leftRightCase(RankedVertex<T> *vertex) {
    RankedVertex<T> *tmp = NULL;
    tmp = rotateLeft(tmp, vertex->left);
    vertex->left = tmp;
    tmp = rotateRight(tmp, vertex);
    updateHeight(tmp->right);
    updateHeight(tmp->left);
    updateHeight(tmp);
    updatei(tmp->right);
    updatei(tmp->left);
    updatei(tmp);
    return tmp;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::rightLeftCase(RankedVertex<T> *vertex) {
    RankedVertex<T> *tmp = NULL;
    tmp = rotateRight(tmp, vertex->right);
    vertex->right = tmp;
    tmp = rotateLeft(tmp, vertex);
    updateHeight(tmp->right);
    updateHeight(tmp->left);
    updateHeight(tmp);
    updatei(tmp->right);
    updatei(tmp->left);
    updatei(tmp);
    return tmp;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::balanceTree(RankedVertex<T> *vertex) {
    int left = (vertex->left == NULL) ? -1 : (vertex->left)->height;
    int right = (vertex->right == NULL) ? -1 : (vertex->right)->height;
    int left_left, right_right, right_left, left_right;

    if (left - right == 2) {

        left_left = ((vertex->left)->left == NULL) ? -1 : ((vertex->left)->left)->height;
        left_right = ((vertex->left)->right == NULL) ? -1 : ((vertex->left)->right)->height;

        if ((left_left - left_right) == 1)
            vertex = leftLeftCase(vertex);
        else if ((left_left - left_right) == -1)
            vertex = leftRightCase(vertex);
        else
            vertex = leftLeftCase(vertex);


    } else if (left - right == -2) {

        right_left = ((vertex->right)->left == NULL) ? -1 : ((vertex->right)->left)->height;
        right_right = ((vertex->right)->right == NULL) ? -1 : ((vertex->right)->right)->height;

        if ((right_left - right_right) == -1)
            vertex = rightRightCase(vertex);
        else if ((right_left - right_right) == 1)
            vertex = rightLeftCase(vertex);
        else
            vertex = rightRightCase(vertex);
    }
    return vertex;
}

template<class T>
bool RankedAVLTree<T>::checkIfBalanced(RankedVertex<T> *vertex) {
    if (!vertex)
        return true;
    if (!(vertex->right) && !(vertex->left))
        return true;
    if (!(vertex->right))
        return (((vertex->left)->height + 1 < 2) && ((vertex->left)->height + 1 > -2));
    if (!(vertex->left))
        return (((vertex->right)->height + 1 < 2) && ((vertex->right)->height + 1 > -2));

    return (((vertex->left)->height - (vertex->right)->height > -2) &&
            ((vertex->left)->height - (vertex->right)->height < 2));
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::insertAux(RankedVertex<T> *vertex, int key, T &data) {
    if (!vertex) {
        RankedVertex<T> *tmp_vertex = new RankedVertex<T>(data, key, 0);
        return tmp_vertex;
    }
    RankedVertex<T> *new_vertex;
    if (compareByKeys(key, vertex->key, data, *vertex->data)) {
        vertex->i++;
        new_vertex = insertAux(vertex->left, key, data);
        vertex->left = new_vertex;
        new_vertex->parent = vertex;
        updateHeight(vertex);
    } else {
        vertex->i++;
        new_vertex = insertAux(vertex->right, key, data);
        vertex->right = new_vertex;
        new_vertex->parent = vertex;
        updateHeight(vertex);

    }
    if (!checkIfBalanced(vertex)) {
        vertex = balanceTree(vertex);
    }
    return vertex;
}

template<class T>
void RankedAVLTree<T>::insert(int key, T &data) {
    if (checkIfContains(root, key, data))
        return;
    root = insertAux(root, key, data);
    number_of_vertexs++;
    root->parent = NULL;
}

template<class T>
int RankedAVLTree<T>::getRankedAVLTreeHeight() const {
    if (!root)
        return -1;
    return root->height;
}

template<class T>
T *RankedAVLTree<T>::getDataAux(RankedVertex<T> *vertex, int key, T &data) {
    if (!vertex)
        return NULL;
    if (vertex->key == key && vertex->data == data)
        return vertex->data;
    if (compareByKeys(key, vertex->key, data, vertex->data))
        return getDataAux(vertex->left, key, data);
    else
        return getDataAux(vertex->right, key, data);
}

template<class T>
T *RankedAVLTree<T>::getData(int key, T &data) const {
    return getDataAux(root, key, data);
}

template<class T>
bool RankedAVLTree<T>::find(int key, T &data) const {
    if (!getData(key, data))
        return false;
    return true;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::findSuccessor(RankedVertex<T> *vertex) {
    RankedVertex<T> *successor = vertex->right;
    while (successor->left)
        successor = successor->left;
    return successor;
}


template<class T>
RankedVertex<T> *RankedAVLTree<T>::removeAux(RankedVertex<T> *vertex, int key, T &data) {
    if (!vertex)
        return NULL;
    RankedVertex<T> *tmp;
    if (vertex->key == key && *vertex->data == data) {
        if (!(vertex->left) || !(vertex->right)) {// one child or zero children
            tmp = (vertex->right) ? vertex->right : vertex->left;
            if (!tmp) {// no children
                tmp = vertex->parent;
                if (!tmp) {//if there is only one vertex
                    delete vertex;
                    return NULL;
                }
                delete vertex;
                return NULL;
            } else {//one child case
                if (!(vertex->parent)) {//if there is only two vertexs
                    tmp->parent = NULL;
                    delete vertex;
                    return tmp;
                } else if ((vertex->parent)->right == vertex) {
                    (vertex->parent)->right = tmp;
                    tmp->parent = vertex->parent;
                } else if ((vertex->parent)->left == vertex) {
                    (vertex->parent)->left = tmp;
                    tmp->parent = vertex->parent;
                }
                delete vertex;
                return tmp;
            }
        } else {// two children
            tmp = findSuccessor(vertex);
            *vertex = *tmp;
            vertex->right = removeAux(vertex->right, tmp->key, *tmp->data);

        }
    } else if (compareByKeys(key, vertex->key, data, *vertex->data))
        vertex->left = removeAux(vertex->left, key, data);
    else
        vertex->right = removeAux(vertex->right, key, data);

    updateHeight(vertex);
    updatei(vertex);
    if (!checkIfBalanced(vertex))
        vertex = balanceTree(vertex);
    return vertex;
}

template<class T>
void RankedAVLTree<T>::remove(int key, T &data) {
    if (!checkIfContains(root, key, data))
        return;
    root = removeAux(root, key, data);
    number_of_vertexs--;
    if (root)
        root->parent = NULL;
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::getVAux(RankedVertex<T> *vertex, int key, T &data) {
    if (!vertex)
        return NULL;
    if (vertex->key == key && *(vertex->data) == data)
        return vertex;
    if (compareByKeys(key, vertex->key, data, *vertex->data))
        return getVAux(vertex->left, key, data);
    else
        return getVAux(vertex->right, key, data);
}

template<class T>
RankedVertex<T> *RankedAVLTree<T>::getV(int key, T &data) {
    return getVAux(root, key, data);
}


#endif //UNTITLED1_RankedAVLTree_H
