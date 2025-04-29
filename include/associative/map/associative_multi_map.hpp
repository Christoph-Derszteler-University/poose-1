#pragma once

#include <vector>
#include <functional>
#include <optional>

#include "container.hpp"

namespace containers::associative {
  template<typename Key, typename Value>
  class associative_multi_map : public container {
  public:
    virtual ~associative_multi_map() override = default;

    /**
     * @brief Inserts a key-value pair into the container.
     * @param key The key to insert.
     * @param value The value associated with the key.
     * @note Multiple values can be associated with the same key.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void insert(const Key& key, const Value& value) = 0;

    /**
     * @brief Checks if any key-value with the specified key exists in the container.
     * @param key The key to search for.
     * @return True if one key-value pair exists, false otherwise.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual bool exists_by_key(const Key& key) const = 0;

    /**
     * @brief Checks if a specific key-value pair exists in the container.
     * @param key The key to search for.
     * @param value The value associated with the key to search for.
     * @return True if the key-value pair exists, false otherwise.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual bool exists(const Key& key, const Value& value) const = 0;

    /**
     * @brief Removes all key-value pairs associated with this key from the container.
     * @param key The key to remove.
     * @note If no key-value pair does not exist, the method has no effect.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void remove_by_key(const Key& key) = 0;

    /**
     * @brief Removes a specific key-value pair from the container.
     * @param key The key to remove.
     * @param value The value associated with the key to remove.
     * @note If the key-value pair does not exist, the method has no effect.
     * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
     */
    virtual void remove(const Key& key, const Value& value) = 0;
  };
}