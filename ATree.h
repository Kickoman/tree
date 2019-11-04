#ifndef ATREE_H_INCLUDED
#define ATREE_H_INCLUDED

#include <set>
#include <iterator>
#include "containers.h"
#include "nodes.h"

template<class T>
class Tree
{
protected:
    BaseNode<T>* _root;

    BaseNode<T>* __getRoot() const;
public:
    Tree() : _root{nullptr}
    {}

    ~Tree()
    {
        delete _root;
    }

    virtual void createRoot(T value) = 0;

    size_t size() const
    {
        return _root->subtreeSize();
    }
};

template<class T>
class OrderedTree : public Tree<T>
{
public:
    void createRoot(T value) override
    {
        if (this->_root)
            delete this->_root;

        this->_root = new OrderedNode<T>(value);
    }

    OrderedNode<T>* getRoot() const
    {
        return static_cast<OrderedNode<T>*>(this->_root);
    }
};

#endif // ATREE_H_INCLUDED
