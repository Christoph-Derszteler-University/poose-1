#pragma once

#include "associative_multi_set.hpp"

namespace containers::associative {
  template<typename Key>
  class ordered_multi_set : public associative_multi_set<Key> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_multi_set() override = default;
  };
}