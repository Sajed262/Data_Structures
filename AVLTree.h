// by sajed
//
//


#ifndef UNTITLED1_AVLTREE_H
#define UNTITLED1_AVLTREE_H

#include <iostream>

template<class T>
class Vertex {
public:
    T *data;
    int key;
    int extra;
    int height;

    class Vertex *left;

    class Vertex *right;

    class Vertex *parent;

    Vertex() = default;

    Vertex(T &data, int key, int extra, int height);

    Vertex(const Vertex &other);

    Vertex &operator=(const Vertex<T> &other);

    ~Vertex();
};

template<class T>
Vertex<T>::Vertex(T &data, int key, int extra, int height) : data(new T(data)), key(key), extra(extra), height(height),
                                                             left(NULL), right(NULL),
                                                             parent(NULL) {
}

template<class T>
Vertex<T>::Vertex(const Vertex<T> &other) {
    this->key = other.key;
    this->height = other.height;
    this->extra = other.extra;
    if (this->data)
        delete this->data;
    this->data = new T(*other.data);
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

template<class T>
Vertex<T> &Vertex<T>::operator=(const Vertex<T> &other) {
    this->key = other.key;
    this->extra = other.extra;
    this->height = other.height;
    if (this->data)
        delete this->data;
    this->data = (new T(*other.data));
    return *this;
}

template<class T>
Vertex<T>::~Vertex<T>() {
    delete data;
}
///////////////////////////////////////////

template<class T>
class AVLTree {
    Vertex<T> *root;
    Vertex<T> *min;
    Vertex<T> *max;
    int number_of_vertexs;

    static void deleteTree(Vertex<T> *root);

    static Vertex<T> *copyAux(Vertex<T> *root1, Vertex<T> *root2);

    static bool compareByKeys(int key1, int key2, bool flag, T &data1, T &data2, int ex1, int ex2);

    static bool checkIfContains(Vertex<T> *root, int key, bool flag, T &data, int ex);

    static void updateHeight(Vertex<T> *vertex);

    static Vertex<T> *rotateRight(Vertex<T> *vertex1, Vertex<T> *vertex2);

    static Vertex<T> *rotateLeft(Vertex<T> *vertex1, Vertex<T> *vertex2);

    static Vertex<T> *leftLeftCase(Vertex<T> *vertex);

    static Vertex<T> *rightRightCase(Vertex<T> *vertex);

    static Vertex<T> *rightLeftCase(Vertex<T> *vertex);

    static Vertex<T> *leftRightCase(Vertex<T> *vertex);

    static Vertex<T> *balanceTree(Vertex<T> *vertex);

    static bool checkIfBalanced(Vertex<T> *vertex);

    static Vertex<T> *insertAux(Vertex<T> *vertex, int key, T &data, int ex, bool flag);

    static T *getDataAux(Vertex<T> *vertex, int key, bool flag);

    static Vertex<T> *getVerAux(Vertex<T> *vertex, int key, int ex, T &Data, bool flag);

    static Vertex<T> *findSuccessor(Vertex<T> *vertex);

    static Vertex<T> *removeAux(Vertex<T> *vertex, int key, T &data, int ex, bool flag);

    static Vertex<T> *FillAux(Vertex<T> *v, int ex, int *array, int size,Vertex<T> *p, int h) {
        if (size <= 0)
            return NULL;
        int mid = size / 2;
        v = new Vertex<T>(array[mid], array[mid], ex, h);
        v->parent = p;
        v->left = FillAux(v->left,ex, array, mid, v,h+1);
        v->right = FillAux(v->right,ex,array+mid+1,size-mid-1,v,h+1);
        return v;
    }


public:

    AVLTree();

    AVLTree(const AVLTree &other);

    AVLTree &operator=(const AVLTree &tree) = default;

    ~AVLTree();

    void insert(int key, T &data, int ex, bool flag);

    int getAVLTreeHeight() const;

    T *getData(int key, bool flag) const;

    Vertex<T> *getVer(int key, int ex, T &Data, bool flag) const;

    bool find(int key) const;

    Vertex<T> *getRoot();

    void remove(int key, T &data, int ex, bool flag);

    void clear();

    Vertex<T> *getMin();

    Vertex<T> *getMax();

    void Fill(int ex, int *array, int size) {
        root = FillAux(root,ex,array,size, nullptr,0);
        number_of_vertexs = size;
        Vertex<T> *tmp = root;
        while (true) {
            if (tmp) {
                if (tmp->left) {
                    tmp = tmp->left;
                    continue;
                }
            }
            min = tmp;
            break;
        }
        tmp = root;
        while (true) {
            if (tmp) {
                if (tmp->right) {
                    tmp = tmp->right;
                    continue;
                }
            }
            max = tmp;
            break;
        }

    }

    bool operator==(const AVLTree<T> other) {
        return true;
    }

    bool operator>(const AVLTree<T> other) {
        return false;
    }

    bool operator<(const AVLTree<T> other) {
        return false;
    }
};


template<class T>
AVLTree<T>::AVLTree() : root(NULL), min(NULL), max(NULL), number_of_vertexs(0) {}

template<class T>
AVLTree<T>::AVLTree(const AVLTree &other): root(NULL), min(NULL), max(NULL), number_of_vertexs(0) {
    root = copyAux(root, other.root);
    number_of_vertexs = other.number_of_vertexs;
    Vertex<T> *tmp = root;
    while (true) {
        if (tmp) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            }
        }
        min = tmp;
        break;
    }
    tmp = root;
    while (true) {
        if (tmp) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            }
        }
        max = tmp;
        break;
    }
}

template<class T>
Vertex<T> *AVLTree<T>::copyAux(Vertex<T> *root1, Vertex<T> *root2) {
    if (!root2)
        return root1;
    root1 = new Vertex<T>(*(root2->data), root2->key, root2->extra, root2->height);
    root1->left = copyAux(root1->left, root2->left);
    if (root1->left)
        root1->left->parent = root1;
    root1->right = copyAux(root1->right, root2->right);
    if (root1->right)
        root1->right->parent = root1;
    return root1;
}

template<class T>
void AVLTree<T>::deleteTree(Vertex<T> *root) {
    if (!root)
        return;
    if (root->left)
        deleteTree(root->left);
    if (root->right)
        deleteTree(root->right);
    delete root;

}

template<class T>
void AVLTree<T>::clear() {
    deleteTree(root);
    root = NULL;
    min = NULL;
    max = NULL;
    number_of_vertexs = 0;
}

template<class T>
AVLTree<T>::~AVLTree() {
    clear();
}

template<class T>
bool AVLTree<T>::compareByKeys(int key1, int key2, bool flag, T &data1, T &data2, int ex1, int ex2) {
    if (!flag) {
        if (key2 != key1) return key2 > key1;
        else if (ex1 != ex2) return ex2 > ex1;
        else return data2 > data1;
    } else {
        if (key2 != key1) return key2 > key1;
        else if (ex1 != ex2) return ex2 < ex1;
        else return data2 < data1;
    }
}

template<class T>
bool AVLTree<T>::checkIfContains(Vertex<T> *root, int key, bool flag, T &data, int ex) {
    if (!root)
        return false;
    if (root->key == key && *(root->data) == data && root->extra == ex)
        return true;
    if (compareByKeys(key, root->key, flag, data, *root->data, ex, root->extra))
        return checkIfContains(root->left, key, flag, data, ex);
    else
        return checkIfContains(root->right, key, flag, data, ex);
}

template<class T>
void AVLTree<T>::updateHeight(Vertex<T> *vertex) {
    if (!vertex)
        return;
    int left = vertex->left == NULL ? -1 : (vertex->left)->height;
    int right = vertex->right == NULL ? -1 : (vertex->right)->height;
    vertex->height = left > right ? left + 1 : right + 1;
}

template<class T>
Vertex<T> *AVLTree<T>::rotateRight(Vertex<T> *vertex1, Vertex<T> *vertex2) {
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
Vertex<T> *AVLTree<T>::rotateLeft(Vertex<T> *vertex1, Vertex<T> *vertex2) {
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
Vertex<T> *AVLTree<T>::leftLeftCase(Vertex<T> *vertex) {
    Vertex<T> *tmp = NULL;
    tmp = rotateRight(tmp, vertex);
    updateHeight(vertex);
    updateHeight(tmp);
    return tmp;
}

template<class T>
Vertex<T> *AVLTree<T>::rightRightCase(Vertex<T> *vertex) {
    Vertex<T> *tmp = NULL;
    tmp = rotateLeft(tmp, vertex);
    updateHeight(vertex);
    updateHeight(tmp);
    return tmp;
}

template<class T>
Vertex<T> *AVLTree<T>::leftRightCase(Vertex<T> *vertex) {
    Vertex<T> *tmp = NULL;
    tmp = rotateLeft(tmp, vertex->left);
    vertex->left = tmp;
    tmp = rotateRight(tmp, vertex);
    updateHeight(tmp->right);
    updateHeight(tmp->left);
    updateHeight(tmp);
    return tmp;
}

template<class T>
Vertex<T> *AVLTree<T>::rightLeftCase(Vertex<T> *vertex) {
    Vertex<T> *tmp = NULL;
    tmp = rotateRight(tmp, vertex->right);
    vertex->right = tmp;
    tmp = rotateLeft(tmp, vertex);
    updateHeight(tmp->right);
    updateHeight(tmp->left);
    updateHeight(tmp);
    return tmp;
}

template<class T>
Vertex<T> *AVLTree<T>::balanceTree(Vertex<T> *vertex) {
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
bool AVLTree<T>::checkIfBalanced(Vertex<T> *vertex) {
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
Vertex<T> *AVLTree<T>::insertAux(Vertex<T> *vertex, int key, T &data, int ex, bool flag) {
    if (!vertex) {
        Vertex<T> *tmp_vertex = new Vertex<T>(data, key, ex, 0);
        return tmp_vertex;
    }
    Vertex<T> *new_vertex;
    if (compareByKeys(key, vertex->key, flag, data, *vertex->data, ex, vertex->extra)) {
        new_vertex = insertAux(vertex->left, key, data, ex, flag);
        vertex->left = new_vertex;
        new_vertex->parent = vertex;
        updateHeight(vertex);
    } else {
        new_vertex = insertAux(vertex->right, key, data, ex, flag);
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
void AVLTree<T>::insert(int key, T &data, int ex, bool flag) {
    if (checkIfContains(root, key, flag, data, ex))
        return;
    root = insertAux(root, key, data, ex, flag);
    number_of_vertexs++;
    root->parent = NULL;
    Vertex<T> *tmp = root;
    while (true) {
        if (tmp->left) {
            tmp = tmp->left;
            continue;
        }
        min = tmp;
        break;
    }
    tmp = root;
    while (true) {
        if (tmp) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            }
        }
        max = tmp;
        break;
    }
}

template<class T>
int AVLTree<T>::getAVLTreeHeight() const {
    if (!root)
        return -1;
    return root->height;
}

template<class T>
T *AVLTree<T>::getDataAux(Vertex<T> *vertex, int key, bool flag) {
    if (!vertex)
        return NULL;
    if (vertex->key == key)
        return vertex->data;
    if (compareByKeys(key, vertex->key, flag, *vertex->data, *vertex->data, vertex->extra, vertex->extra))
        return getDataAux(vertex->left, key, flag);
    else
        return getDataAux(vertex->right, key, flag);
}

template<class T>
T *AVLTree<T>::getData(int key, bool flag) const {
    return getDataAux(root, key, flag);
}

template<class T>
bool AVLTree<T>::find(int key) const {
    if (!getData(key, false))
        return false;
    return true;
}

template<class T>
Vertex<T> *AVLTree<T>::getVerAux(Vertex<T> *vertex, int key, int ex, T &Data, bool flag) {
    if (!vertex)
        return NULL;
    if (vertex->key == key && vertex->extra == ex && *(vertex->data) == Data)
        return vertex;
    if (compareByKeys(key, vertex->key, flag, Data, *vertex->data, ex, vertex->extra))
        return getVerAux(vertex->left, key, ex, Data, flag);
    else
        return getVerAux(vertex->right, key, ex, Data, flag);
}

template<class T>
Vertex<T> *AVLTree<T>::getVer(int key, int ex, T &Data, bool flag) const {
    return getVerAux(root, key, ex, Data, flag);
}

template<class T>
Vertex<T> *AVLTree<T>::getRoot() {
    return root;
}

template<class T>
Vertex<T> *AVLTree<T>::findSuccessor(Vertex<T> *vertex) {
    Vertex<T> *successor = vertex->right;
    while (successor->left)
        successor = successor->left;
    return successor;
}


template<class T>
Vertex<T> *AVLTree<T>::removeAux(Vertex<T> *vertex, int key, T &data, int ex, bool flag) {
    if (!vertex)
        return NULL;
    Vertex<T> *tmp;
    if (vertex->key == key && *(vertex->data) == data && vertex->extra == ex) {
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
            vertex->right = removeAux(vertex->right, tmp->key, *tmp->data, tmp->extra, flag);

        }
    } else if (compareByKeys(key, vertex->key, flag, data, *vertex->data, ex, vertex->extra))
        vertex->left = removeAux(vertex->left, key, data, ex, flag);
    else
        vertex->right = removeAux(vertex->right, key, data, ex, flag);

    updateHeight(vertex);
    if (!checkIfBalanced(vertex))
        vertex = balanceTree(vertex);
    return vertex;
}

template<class T>
void AVLTree<T>::remove(int key, T &data, int ex, bool flag) {
    if (!checkIfContains(root, key, flag, data, ex))
        return;
    root = removeAux(root, key, data, ex, flag);
    number_of_vertexs--;
    Vertex<T> *tmp = root;
    if (root)
        root->parent = NULL;
    else
        min = root;
    if (!root)
        return;
    while (true) {
        if (tmp) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            }
        }
        min = tmp;
        break;
    }
    tmp = root;
    while (true) {
        if (tmp->right) {
            tmp = tmp->right;
            continue;
        }
        max = tmp;
        break;
    }
}


template<class T>
Vertex<T> *AVLTree<T>::getMin() {
    return min;
}

template<class T>
Vertex<T> *AVLTree<T>::getMax() {
    return max;
}


#endif //UNTITLED1_AVLTREE_H
