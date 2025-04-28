#pragma once

#include "sequential/abstract_stack.hpp"
#include <list>

namespace containers::sequential {

    template <typename T>
    class list_stack: public abstract_stack<T> {
    private:
        auto list;
        size_t size;
    public:
        /**
         * @brief constructs a stack using the list structure
         */
        list_stack();

        //! @copydoc abstract_stack::push
        void push(const T& data);

        //! @copydoc abtract_stack::pop
        T pop();

        //! @copydoc abstract_stack::isEmpty
        bool isEmpty();

        //! @copydoc abstract_stack::size
        size_t size();

    };
}

#include "inline/list_stack.tpp"