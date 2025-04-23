#pragma once

#include <functional>
#include <container.hpp>

namespace containers::associative {
  template<typename Key>
  class ordered_set : public associative_set<Key> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_set() override = default;
  };
}