#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED

#include "containers.h"

template<class T>
class BaseNode
{
protected:
    using NodePtr = BaseNode<T>*;

    T *_data;
    NodePtr _parent;
    BaseContainer<NodePtr> *_children;

    virtual void __createChildrenContainer() = 0;

public:
    BaseNode() : _data{nullptr}, _parent{nullptr}, _children{nullptr}
    {
        __createChildrenContainer();
    }

    BaseNode(T data) : BaseNode()
    {
        _data = new T(data);
    }

    BaseNode(T data, NodePtr parent) : BaseNode(data)
    {
        _parent = parent;
        parent->addChild(this);
    }

    ~BaseNode()
    {
        for (auto it = _children->cbegin(); it != _children->cend(); it++)
            delete *it;
        delete _data;
    }

    void addChild(NodePtr child)
    {
        _children.add(child);
    }

    virtual void addChild(T childValue) = 0;

    bool isRoot()
    {
        return nullptr == _parent;
    }

    size_t subtreeSize() const
    {
        if (_children->empty())
            return 1;

        size_t sz = 1;  // including current
        for (auto it = _children->cbegin(); it != _children->cend(); it++)
            sz += (*it)->subtreeSize();
        return sz;
    }
};


template<class T>
class OrderedNode : public BaseNode<T>
{
protected:
    void __createChildrenContainer() override
    {
        this->_children = new std::vector<T>;
    }

public:
    OrderedNode() : BaseNode<T>() {}
    OrderedNode(T value) : BaseNode<T>(value) {}

    void addChild(T childValue) override
    {
        auto tmpValue = new OrderedNode<T>(childValue);
        BaseNode<T>::addChild(tmpValue);
    }
};

template<class T>
class SortedNode : public BaseNode<T>
{
protected:
    void __createChildrenContainer() override
    {
        this->_children = new std::multiset<T>;
    }
public:
    void addChild(T childValue) override
    {
        auto tmpValue = new SortedNode<T>(childValue);
        addChild(tmpValue);
    }
};

#endif // NODES_H_INCLUDED
