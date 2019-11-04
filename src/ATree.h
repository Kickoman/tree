#ifndef ATREE_H_INCLUDED
#define ATREE_H_INCLUDED

#include <set>
#include <iterator>
#include "nodes.h"

template<class T, template<class> class N> // type, Node type
class Tree
{
protected:
    N<T> *_root;

public:
    Tree() :_root{nullptr}
    {}

    ~Tree()
    {
        delete _root;
    }

    void createRoot(T value)
    {
        if (_root)
            delete _root;

        _root = new N<T>(value);
    }

    size_t size() const
    {
        return _root->subtreeSize();
    }

    N<T> *getRoot() const
    {
        return _root;
    }
};

template<class T>
using OrderedTree = Tree<T, OrderedNode>;

template<class T>
using SortedTree = Tree<T, SortedNode>;

#endif // ATREE_H_INCLUDED
