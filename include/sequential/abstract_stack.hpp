#pragma once

#include "../container.hpp"

namespace containers::sequential {
    template<typename T>
    class abstract_stack : public container {
    public:
        virtual ~stack() override = default;
        
        /**
         * @brief Inserts a value at the front of the container
         * @param data The value to be stored
         */
        virtual void push(const T& data) =0;

        /**
         * @brief Deletes & returns the value at front of the container
         * @return a value of Type data
         */
        virtual T pop() = 0;

        /**
         * @brief Checks if the container is empty
         * @return True if empty, False else
         */
        virtual bool isEmpty() = 0;
        /**
        * @brief Returns the number of elements in the container.
        * @return The size of the container.
        * @note This method has a runtime complexity of O(1).
        */
       virtual const size_t size() override;

    };
}