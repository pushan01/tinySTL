#ifndef TINYSTL_STACK_H
#define TINYSTL_STACK_H

#include "deque.h"

namespace tinySTL {
    template <class T, class Container = deque<T>>
    class stack {
        friend bool operator==<>(const stack &left, const stack &right);
        friend bool operator!=<>(const stack &left, const stack &right);
        friend bool operator< <>(const stack &left, const stack &right);
        friend bool operator<=<>(const stack &left, const stack &right);
        friend bool operator> <>(const stack &left, const stack &right);
        friend bool operator>=<>(const stack &left, const stack &right);

    public:
        using container_type    = Container;
        using value_type        = typename Container::value_type;
        using size_type         = typename Container::size_type;
        using reference         = typename Container::reference;
        using const_reference   = typename Container::const_reference;

    private:
        Container c;

    public:
        stack() = default;

        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        reference top() {
            return c.back();
        }

        const_reference top() const {
            return c.back();
        }

        void push(const_reference value) {
            c.push_back(value);
        }

        void pop() {
            c.pop_back();
        }
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &left, const stack<T, Container> &right) {
        return left.c == right.c;
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &left, const stack<T, Container> &right) {
        return left.c < right.c;
    }
}


#endif //TINYSTL_STACK_H