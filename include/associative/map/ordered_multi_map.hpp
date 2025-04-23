#pragma once

#include "associative_multi_map.hpp"

namespace containers::associative {
  template<typename Key, typename Value>
  class ordered_multi_map : public associative_multi_map<Key, Value> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_multi_map() override = default;
  };
}