#pragma once

#include "../container.hpp"

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
    virtual const bool exists(const Key& key) = 0;

    /**
       * @brief Removes a key from the container.
       * @param key The key to remove.
       * @note If the key does not exist, the method has no effect.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual void remove(const Key& key) = 0;
  };

  template<typename Key>
  class associative_multi_set : public container {
  public:
    virtual ~associative_multi_set() override = default;

    /**
       * @brief Inserts a key into the container.
       * @param key The key to insert.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual void insert(const Key& key) = 0;

    /**
       * @brief Checks if a key exists in the container.
       * @param key The key to search for.
       * @return True if the key exists at least once, false otherwise.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual const bool exists(const Key& key) = 0;

    /**
       * @brief Removes a key from the container.
       * @param key The key to remove.
       * @note If the key does not exist in the container, the method has no effect.
       * @note Runtime complexity: O(log n) for ordered containers, O(1) on average for hash-based containers.
       */
    virtual void remove(const Key& key) = 0;
  };

  template<typename Key>
  class ordered_set : public associative_set<Key> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_set() override = default;
  };

  template<typename Key>
  class ordered_multi_set : public associative_set<Key> {
    // Adding a virtual destructor, because this class is not going to be implemented
    virtual ~ordered_multi_set() override = default;
  };

  template<typename Key>
  class hashing_set : public associative_set<Key> {
  };

  template<typename Key>
  class hashing_multi_set : public associative_multi_set<Key> {
  };
}