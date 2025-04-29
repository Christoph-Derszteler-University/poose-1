#pragma once
#include "abstract_queue.hpp"
//TODO: change std::list with own implementation doubly_linked_list
#include <list>

namespace containers::sequential{
    
    /**
    * @brief A generic queue implementation.
    *
    * Provides standard operations for enqueueing, and dequeueing
    * in a doubly linked structure.
    *
    * @tparam T The type of the elements stored in the queue.
    */
    template<typename T>
    class list_queue final : public abstract_queue<T>{
        public:
        /**
         * @brief constructs a new empty queue
         */
        list_queue();

        //! @copydoc abstract_queue::enqueue
        void enqueue(const T& data) override;

        //! @copydoc abstract_queue::dequeue
        T dequeue() override;

        //! @copydoc abstract_queue::is_empty
        bool is_empty() const noexcept override;

        private:
        std::list<T> m_list;
    };
}

#include "sequential/inline/list_queue.tpp"