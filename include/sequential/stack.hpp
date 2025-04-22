#pragma once

#include "../container.hpp"

namespace containers::sequential {
    template<typename T>
    class stack : public container {
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

    };
}