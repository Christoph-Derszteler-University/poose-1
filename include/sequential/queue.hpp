#pragma once

#include "../container.hpp"

namespace containers::sequential {
    template<typename data>
    class queue : public container {
    public:
        virtual ~queue() override = default;
        
        virtual void add(data) =0;

        virtual data pop() = 0;
    };
}