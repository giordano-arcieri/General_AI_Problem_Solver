#ifndef NODE_HPP
#define NODE_HPP

// I am using standerd shared pointers instead of raw ones. This means I dont need a destructor and it makes things a lot simpler/safer. There are some benifits to raw pointers that might make you want to switch to them.
#include <memory>

#include <ostream>

// This is a simple struct. Maybe it would be better to use get and set functions instead or have some added interface.
template <typename T>
struct Node
{
    T value;
    std::shared_ptr<Node<T>> next;

    Node(const T &value, const std::shared_ptr<Node<T>>& next = nullptr)
        : value(value), next(next) {}

    bool operator!=(const Node<T> &other) const
    {
        return this->value != other.value;
    }

    bool operator==(const T &other) const
    {
        return this->value == other;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node<T>& node)
    {
        os << node.value << "->";
        if(node.next != nullptr)
            os << *node.next;
        else
            os << "NULL";
        return os;
    }
};

#endif