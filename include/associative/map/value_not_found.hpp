#pragma once

#include <exception>

namespace containers::associative {
  template<typename Key>
  class value_not_found final : public std::exception {
  public:
    explicit value_not_found(const Key& key);

    virtual const char* what() const noexcept override;
    const Key& key() const;
  private:
    const Key& associated_key;
  };
}

#include "inline/value_not_found.tpp"