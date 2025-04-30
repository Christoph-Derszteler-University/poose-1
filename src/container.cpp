#include "container.hpp"

containers::size_t containers::container::size() const noexcept {
  return number_elements;
}

bool containers::container::empty() const noexcept {
  return size() == 0;
}
