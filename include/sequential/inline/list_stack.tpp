#include "sequential/list_stack.hpp"

namespace containers::sequential {

    template <typename T> list_stack<T>::list_stack() : m_list() {
        m_size = 0;
    }
    template <typename T> void list_stack<T>::push(const T& data) {
        m_list.push_front(data);
        m_size ++;
    }
    template <typename T> T list_stack<T>::pop() {
        T tmp = m_list.front();
        m_list.pop_front();
        m_size += -1;
        return tmp;
    }
    template <typename T> bool list_stack<T>::isEmpty() {
        return (m_size == 0);
    }
    template <typename T> const size_t list_stack<T>::size() {
        return m_size;
    }

}