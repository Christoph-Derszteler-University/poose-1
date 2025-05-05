#pragma once

#include <exception>

namespace containers::sequential {

class invalid_node final : public std::exception {
public:
  virtual const char *what() const noexcept override;
};

} // namespace containers::sequential

#include "inline/invalid_node.tpp"
