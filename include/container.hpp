#pragma once
#include <cstddef>

namespace containers {
  using size_t = std::size_t;
  using hash_t = int;

  /**
   * @brief Abstract base class representing a generic container.
   */
  class container {
  public:
    virtual ~container() = default;

    /**
     * @brief Returns the number of elements in the container.
     * @return The size of the container.
     * @note This method has a runtime complexity of O(1).
     */
    [[nodiscard]] size_t size() const noexcept;

    /**
    * @brief Returns whether the container is empty or not
    * @return true if number_elements is greater than 0 else 0
    * @note This method has a runtime complexity of O(1).
    */
    [[nodiscard]] bool empty() const noexcept;
  protected:
    size_t number_elements = 0;
  };
}
