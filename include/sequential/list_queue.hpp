#pragma once
#include "abstract_queue.hpp"

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

        //! @copydoc abstract_queue::isEmpty
        bool isEmpty() override;

        /**
        * @brief Returns the number of elements in the queue.
        * @return The size of the queue.
        * @note This method has a runtime complexity of O(1).
        */
        const size_t size() override;

        private:

        size_t length;

        //yet to be implemented by using class doubly_linked_list
        //head = 
        //tail =

    };
}

#include "sequential/inline/list_queue.tpp"