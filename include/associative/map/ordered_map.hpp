#pragma once

#include "associative_map.hpp"

namespace containers::associative {
  template<typename Key, typename Value>
  class ordered_map : public associative_map<Key, Value> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_map() override = default;
  };
}