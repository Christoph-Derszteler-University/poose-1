#include "sequential/list_stack.hpp"

namespace containers::sequential {

    template <typename T> list_stack<T>::list_stack() {}

    template <typename T> void list_stack<T>::push(const T& data) {
        m_list.push_front(data);
        container::number_elements++;
    }
    template <typename T> T list_stack<T>::pop() {
        T tmp = m_list.front();
        m_list.pop_front();
        container::number_elements -= 1;
        return tmp;
    }
    template <typename T> bool list_stack<T>::is_empty() const noexcept {
        return container::number_elements == 0;
    }
}
