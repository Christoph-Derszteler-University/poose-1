#pragma once

namespace containers::sequential {
const char *invalid_node::what() const noexcept {
  return "The node is a nullptr and therefore invalid.";
};
} // namespace containers::sequential
