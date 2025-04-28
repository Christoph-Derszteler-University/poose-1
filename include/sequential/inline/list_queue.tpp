#include "sequential/list_queue.hpp"

namespace containers::sequential {

    template <typename T> list_queue<T>::list_queue() : m_list() {
        length = 0;
    }

    template <typename T> void list_queue<T>::enqueue(const T& data){
        m_list.push_back(data);
        length++;
    }
    template <typename T> T list_queue<T>::dequeue(){
        T tmp = m_list.front();
        m_list.pop_front();
        length--;
        return tmp;
    }
    template <typename T> bool list_queue<T>::isEmpty(){
        return (length == 0);
    }
    template <typename T> const size_t list_queue<T>::size(){
        return length;
    }
}