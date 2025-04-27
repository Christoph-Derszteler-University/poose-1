#pragma once

#include <format>

namespace containers::associative {
  template<typename Key>
  duplicate_key<Key>::duplicate_key(const Key& key) : associated_key(key)  {}

  template<typename Key>
  const char* duplicate_key<Key>::what() const noexcept {
    return std::format("duplicate key {}", key).c_str();
  }

  template<typename Key>
  const Key& duplicate_key<Key>::key() const {
    return key;
  }
}