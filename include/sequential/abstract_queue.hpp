#pragma once

#include "../container.hpp"

namespace containers::sequential {
    template<typename T>
    class abstract_queue : public container {
    public:
        virtual ~queue() override = default;
        
        /**
         * @brief Inserts a value at the end of the container
         * @param data The value to be stored
         */
        virtual void enqueue(const T& data) =0;

        /**
         * @brief Deletes & returns the value at front of the container
         * @return a value of Type data
         */
        virtual T dequeue() = 0;

        /**
         * @brief Checks if the container is empty
         * @return True if empty, False else
         */
        virtual bool isEmpty() = 0;

    };
}