#include "sequential/list_stack.hpp"
#include "sequential/empty_container.hpp"

namespace containers::sequential {

    template <typename T> list_stack<T>::list_stack() {}

    template <typename T> void list_stack<T>::push(const T& data) {
        m_list.push_front(data);
        container::number_elements++;
    }
    template <typename T> T list_stack<T>::pop() {
        if (m_list.empty()){
            throw empty_container();
        }
        const auto& tmp = m_list.front();
        m_list.pop_front();
        container::number_elements--;
        return tmp->data;
    }
    template <typename T> const T& list_stack<T>::top() const {
        if (m_list.empty()){
            throw empty_container();
        }
        return m_list.front()->data;
    }
}
