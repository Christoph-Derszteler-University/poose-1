#include "sequential/list_queue.hpp"

namespace containers::sequential {

    template <typename T> list_queue<T>::list_queue() : m_list(), m_length(0) {}

    template <typename T> void list_queue<T>::enqueue(const T& data){
        m_list.push_back(data);
        m_length++;
    }
    template <typename T> T list_queue<T>::dequeue(){
        T tmp = m_list.front();
        m_list.pop_front();
        m_length--;
        return tmp;
    }
    template <typename T> bool list_queue<T>::isEmpty() const noexcept{
        return (m_length == 0);
    }
    template <typename T> const size_t list_queue<T>::size(){
        return m_length;
    }
}