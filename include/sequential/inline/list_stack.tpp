#include "sequential/list_stack.hpp"

namespace containers::sequential {

    template <typename T> list_stack<T>::list_stack() {
        list = std::list<T>;
        size = 0;
    }
    template <typename T> void list_stack<T>::push(const T& data) {
        list.push_back(data);
        size ++;
    }
    template <typename T> T list_stack<T>::pop() {
        return list.pop_front();
        size += -1;
    }
    template <typename T> bool list_stack<T>::isEmpty() {
        return (size == 0);
    }
    template <typename T> size_t list_stack<T>::size() {
        return size;
    }


}