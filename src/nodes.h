#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED

#include <set>
#include <vector>

template<class T, template<typename...> class C>
class Node
{
protected:
    using NodePtr = Node<T, C>*;

    T                     *_data;
    NodePtr                _parent;
    C<Node<T, C>*>         _children;

public:
    Node() : _data{nullptr}, _parent{nullptr}
    {}

    Node(T data) : Node()
    {
        _data = new T(data);
    }

    Node(T data, NodePtr parent) : Node(data)
    {
        _parent = parent;
        _parent->addChild(this);
    }

    ~Node()
    {
        for (auto it = _children.cbegin(); it != _children.cend(); it++)
            delete *it;
        delete _data;
    }

    void addChild(NodePtr child)
    {
        child->setParent(this);
        _children.insert(_children.end(), child);
    }

    void addChild(T value)
    {
        auto tmpPtr = new Node<T, C>(value);
        addChild(tmpPtr);
    }

    bool denyChild(NodePtr child)
    {
        for (auto it = _children.begin(); it != _children.end(); it++)
        {
            if (*it == child)
            {
                child->setParent(nullptr);
                _children.erase(it);
                return true;
            }
        }
        return false;
    }

    void setParent(NodePtr parent)
    {
        if (_parent)
        {
            _parent->denyChild(this);
        }

        _parent = parent;
    }

    bool isRoot()
    {
        return nullptr == _parent;
    }

    size_t subtreeSize() const
    {
        size_t size = 1;
        for (auto it = _children.cbegin(); it != _children.cend(); it++)
            size += (*it)->subtreeSize();
        return size;
    }
};

template<class T>
using SortedNode = Node<T, std::set>;

template<class T>
using OrderedNode = Node<T, std::vector>;

#endif // NODES_H_INCLUDED
