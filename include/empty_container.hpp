#pragma once
#include <exception>

namespace containers{
    class empty_container  : public std::exception {
    public:
    virtual const char* what() const noexcept override;
    };
}