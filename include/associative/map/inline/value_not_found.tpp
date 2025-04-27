#pragma once

#include <format>

namespace containers::associative {
  template<typename Key>
  value_not_found<Key>::value_not_found(const Key& key) : associated_key(key)  {}

  template<typename Key>
  const char* value_not_found<Key>::what() const noexcept {
    return std::format("could not find value for key {}", key).c_str();
  }

  template<typename Key>
  const Key& value_not_found<Key>::key() const {
    return key;
  }
}