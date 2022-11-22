// by sajed
//
//

#ifndef WET2_MVNI_HASHTABLENEW_HPP
#define WET2_MVNI_HASHTABLENEW_HPP

#include "List.h" // the list in the same repo.
#include <iostream>

using std::ostream;

#define SIZE 2

static inline int findIndexForHash(int key, int size) // hashing function
{
    double a = 0.61803398875;
    double temp = key * a;
    int temp2 = temp;
    temp = (temp - temp2) * size;
    temp2 = temp;
    return temp2;
}

template <class T>
class Cell
{
    List<T> data;
    int size;

public:
    Cell() : data(), size(0) {}

    ~Cell() = default;

    Cell(const Cell &other) = default;

    T *findData(int key)
    {
        return data.getElement(key);
    }

    Node<T> *getFirst()
    {

        return data.getFirstKey();
    }

    Node<T> *getNext()
    {
        return data.getNextKey();
    }

    void reinsert(int key, T *dat)
    {
        size++;
        data.addElement(key, *dat);
    }

    int insert(int key, T &dat)
    {
        if (!(data.getElement(key)))
        {

            data.addElement(key, dat);
            size++;
            return 0;
        }
        return -1;
    }

    int remove(int key)
    {
        data.removeElement(key);
        size--;
        return size;
    }

    void clearCell()
    {
        data.clearList();
    }
};

template <class T>
class HashTable // based on chain hashing.
{
    int size;
    int numOfKeys;
    Cell<T> **table;
    
    static void resize(HashTable &ht);

    static void reinsert(Cell<T> **new_table, int new_size, Node<T> *data);

public:
    HashTable() : size(SIZE), numOfKeys(0)
    {
        table = (new Cell<T> *[SIZE]);
        for (int i = 0; i < size; ++i)
        {
            table[i] = nullptr;
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < size; ++i)
        {
            delete table[i];
        }
        delete[] table;
    }

    T *findData(int key)
    {
        int index = findIndexForHash(key, size);
        if (!table[index])
            return nullptr;
        return (table[index])->findData(key);
    }

    int insert(int key, T &data)
    {
        int index = findIndexForHash(key, size);
        Cell<T> *cell = table[index];
        if (!cell)
        {
            cell = new Cell<T>();
            table[index] = cell;
        }
        int result = cell->insert(key, data);
        if (result != 0)
            return -1;
        numOfKeys++;
        if (numOfKeys >= size || numOfKeys <= (size / 4))
            resize(*this);
        return 0;
    }

    int remove(int key)
    {
        T *tmp = findData(key);
        if (!tmp)
            return -1;
        int index = findIndexForHash(key, size);
        Cell<T> *cell = table[index];
        if (cell->remove(key) == 0)
        {
            table[index] = nullptr;
        }
        numOfKeys--;
        return 0;
    }

    void clearTable(Cell<T> **tabl)
    {
        for (int i = 0; i < size; i++)
        {
            if (tabl[i])
                tabl[i]->clearCell();
            delete tabl[i];
        }
        delete[] tabl;
    }

    int getSize() { return size; }

    int getNumOfKeys() { return numOfKeys; }

    friend ostream &operator<<(ostream &os, HashTable *ht)
    {
        os << "Printing the elements:" << std::endl;

        int elem = 0;
        for (size_t i = 0; i < ht->getSize(); i++)
        {
            if (!(ht->table[i]))
                continue;
            os << "     Printing elements in cell " << i << ": " << std::endl;
            Node<T> *tmp = ht->table[i]->getFirst();
            while (tmp)
            {
                os << "         key: " << tmp->key << ", data: " << *(tmp->data) << ", element number: " << ++elem << "." << std::endl;
                tmp = ht->table[i]->getNext();
            }
        }
        os << "Number of elements: " << elem << ", Number of keys: " << ht->getNumOfKeys() << std::endl;
        return os;
    }
};

template <class T>
void HashTable<T>::resize(HashTable<T> &ht) // the hash gets bigger by 2 OR the hash gets smaller by 2
{
    int old_size = ht.size;
    if (ht.numOfKeys >= ht.size) // we want to copy the old table to the new one,
    {                            // because the keys are equal or bigger than the size of the table.
        int new_size = 2 * old_size;
        Cell<T> **new_table = new Cell<T> *[new_size];
        for (int j = 0; j < new_size; ++j)
        {
            new_table[j] = nullptr;
        }
        Cell<T> **old_table = ht.table;
        ht.table = new_table;

        for (int i = 0; i < old_size; ++i)
        {
            if (old_table[i])
            {
                Node<T> *current = old_table[i]->getFirst();
                while (current)
                {
                    ht.reinsert(new_table, new_size, current);
                    current = old_table[i]->getNext();
                }
            }
        }
        ht.clearTable(old_table);
        ht.size = new_size;

        return;
    }
    // if we get here then the table has shrinked to quarter
    int new_size = (old_size / 2) + 1;
    Cell<T> **new_table = new Cell<T> *[new_size];
    for (int j = 0; j < new_size; ++j)
    {
        new_table[j] = nullptr;
    }
    Cell<T> **old_table = ht.table;
    ht.table = new_table;

    for (int i = 0; i < old_size; ++i)
    {
        if (old_table[i])
        {
            Node<T> *current = old_table[i]->getFirst();
            while (current)
            {
                ht.reinsert(new_table, new_size, current);
                current = old_table[i]->getNext();
            }
        }
    }

    ht.clearTable(old_table);
    ht.size = new_size;
}

template <class T>
void HashTable<T>::reinsert(Cell<T> **new_table, int new_size, Node<T> *node)
{
    int index = findIndexForHash(node->key, new_size);
    Cell<T> *cell = new_table[index];
    if (!cell)
    {
        cell = new Cell<T>();
        new_table[index] = cell;
    }
    cell->reinsert(node->key, (node->data));
}

#endif // WET2_MVNI_HASHTABLENEW_HPP
