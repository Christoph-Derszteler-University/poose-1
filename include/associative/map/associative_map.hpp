#pragma once

#include <vector>
#include <functional>
#include <optional>

#include "container.hpp"

namespace containers::associative {
  template<typename Key, typename Value>
  class associative_map : public container {
  public:
    virtual ~associative_map() override = default;

    /**
     * @brief Inserts a key-value pair into the container.
     * @param key The key to insert.
     * @param value The value associated with the key.
     * @note If the key already exists, the value may be updated depending on the implementation.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void insert(const Key& key, const Value& value) = 0;

    /**
     * @brief Checks if a key exists in the container.
     * @param key The key to search for.
     * @return True if the key exists, false otherwise.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual std::optional<Value> find_by_key(const Key& key) const = 0;

    /**
     * @brief Removes a key and its associated value from the container.
     * @param key The key to remove.
     * @note If the key does not exist, the method has no effect.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void remove(const Key& key) = 0;
  };
}