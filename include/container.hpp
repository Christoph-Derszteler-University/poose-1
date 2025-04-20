#pragma once
#include <cstddef>

namespace containers {
using size_t = std::size_t;

class container {
  public:
    virtual ~container() = default;
    virtual size_t size() = 0;
};
}