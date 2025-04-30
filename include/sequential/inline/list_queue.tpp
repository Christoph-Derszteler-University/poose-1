#include "sequential/list_queue.hpp"
#include "sequential/empty_container.hpp"

namespace containers::sequential {

    template <typename T> list_queue<T>::list_queue(){}

    template <typename T> void list_queue<T>::enqueue(const T& data){
        m_list.push_back(data);
        container::number_elements++;
    }
    template <typename T> T list_queue<T>::dequeue(){
        if (m_list.empty()){
            throw empty_container();
        }
        T tmp = m_list.front();
        m_list.pop_front();
        container::number_elements--;
        return tmp;
    }
    template <typename T> const T& list_queue<T>::front() const{
        if (m_list.empty()){
            throw empty_container();
        }
        return m_list.front();
    }
    template <typename T> const T& list_queue<T>::back() const {
        if (m_list.empty()){
            throw empty_container();
        }
        return m_list.back();

    }
}
