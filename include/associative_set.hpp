#pragma once

#include "container.hpp"
#include "vector"
#include "functional"

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
    virtual const bool exists(const Key& key) = 0;

    /**
       * @brief Removes a key and its associated value from the container.
       * @param key The key to remove.
       * @note If the key does not exist, the method has no effect.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual void remove(const Key& key) = 0;
  };

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
       * @brief Checks if a specific key-value pair exists in the container.
       * @param key The key to search for.
       * @param value The value associated with the key to search for.
       * @return True if the key-value pair exists, false otherwise.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual const bool exists(const Key& key, const Value& value) = 0;

    /**
       * @brief Removes a specific key-value pair from the container.
       * @param key The key to remove.
       * @param value The value associated with the key to remove.
       * @note If the key-value pair does not exist, the method has no effect.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual void remove(const Key& key, const Value& value) = 0;
  };

  template<typename Key, typename Value>
  class ordered_map : public associative_map<Key, Value> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_map() override = default;
  };

  template<typename Key, typename Value>
  class ordered_multi_map : public associative_map<Key, Value> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_multi_map() override = default;
  };

  template<typename Key, typename Value>
  class hashing_map : public associative_map<Key, Value> {
  };

  template<typename Key, typename Value>
  class hashing_multi_map : public associative_map<Key, Value> {
  };
}