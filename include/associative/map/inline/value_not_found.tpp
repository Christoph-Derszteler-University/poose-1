#pragma once

#include <format>

namespace containers::associative {
  template<typename Key>
  value_not_found<Key>::value_not_found(const Key& key) :
    associated_key(key),
    message(std::format("could not find value for key {}", key).c_str())
  {}

  template<typename Key>
  const char* value_not_found<Key>::what() const noexcept {
    return message.data();
  }

  template<typename Key>
  const Key& value_not_found<Key>::key() const {
    return associated_key;
  }
}