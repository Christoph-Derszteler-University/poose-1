#pragma once

#include "sequential/abstract_stack.hpp"
#include "doubly_linked_list.hpp"

namespace containers::sequential {

    template <typename T>
    class list_stack: public abstract_stack<T> {
    private:
        doubly_linked_list<T> m_list;
    public:
        /**
         * @brief constructs a stack using the list structure
         */
        list_stack();

        //! @copydoc abstract_stack::push
        void push(const T& data) override;

        //! @copydoc abtract_stack::pop
        T pop() override;

        //! @copydoc abstract_stack::top
        const T& top() const override;
    };
}

#include "inline/list_stack.tpp"
