#include "sequential/list_queue.hpp"

namespace containers::sequential {

    template <typename T> list_queue<T>::list_queue(){}

    template <typename T> void list_queue<T>::enqueue(const T& data){
        m_list.push_back(data);
        container::number_elements++;
    }
    template <typename T> T list_queue<T>::dequeue(){
        T tmp = m_list.front();
        m_list.pop_front();
        container::number_elements--;
        return tmp;
    }
}
