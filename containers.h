#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include <vector>
#include <set>

template<class T>
class BaseContainer
{
public:
    virtual void add(T value) = 0;
};


template<class T>
class OrderedContainer : public BaseContainer<T>, public std::vector<T>
{
public:
    void add(T value) override
    {
        this->push_back(value);
    }
};


template<class T>
class SortedContainer : public BaseContainer<T>, public std::multiset<T>
{
public:
    void add(T value) override
    {
        this->insert(value);
    }
};


#endif // CONTAINERS_H_INCLUDED
