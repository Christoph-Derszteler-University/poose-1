#include "sequential/list_stack.hpp"

namespace containers::sequential {

    template <typename T> list_stack<T>::list_stack() {
        list = std::list<T>;
        size = 0;
    }
    template <typename T> void list_stack<T>::push(const T& data) {
        list.push_front(data);
        size ++;
    }
    template <typename T> T list_stack<T>::pop() {
        T tmp = list.front();
        list.pop_front();
        size += -1;
        return tmp;
    }
    template <typename T> bool list_stack<T>::isEmpty() {
        return (size == 0);
    }
    template <typename T> const size_t list_stack<T>::size() {
        return size;
    }


}