#pragma once

#include <container.hpp>

namespace containers::associative {
  template<typename Key>
  class associative_set : public container {
  public:
    virtual ~associative_set() override = default;

    /**
     * @brief Inserts a key into the container.
     * @param key The key to insert.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void insert(const Key& key) = 0;

    /**
     * @brief Checks if a key exists in the container.
     * @param key The key to search for.
     * @return True if the key exists, false otherwise.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual bool exists(const Key& key) const = 0;

    /**
     * @brief Removes a key from the container.
     * @param key The key to remove.
     * @note If the key does not exist, the method has no effect.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void remove(const Key& key) = 0;
  };
}