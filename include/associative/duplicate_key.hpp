#pragma once

#include <exception>
#include <string>

namespace containers::associative {
  template<typename Key>
  class duplicate_key final : public std::exception {
  public:
    explicit duplicate_key(const Key& key);

    virtual const char* what() const noexcept override;
    const Key& key() const;
  private:
    const Key associated_key;
    const std::string message;
  };
}

#include "inline/duplicate_key.tpp"