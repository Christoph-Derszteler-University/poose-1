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

  /**
   * @class hash_map
   * @brief A hash-based associative map implementation.
   *
   * This class provides an efficient hash-based implementation of an associative map,
   * where each key is associated with a single value. It uses a hash function to
   * distribute keys into buckets, ensuring average O(1) runtime complexity for
   * insertion, lookup, and removal operations.
   *
   * @tparam Key The type of the keys stored in the map.
   * @tparam Value The type of the values associated with the keys.
   *
   * @details
   * - The map uses a vector of buckets, where each bucket is a vector of tuples
   *   containing the key, value, and the computed hash.
   * - The number of buckets can grow dynamically to maintain a low load factor,
   *   ensuring efficient operations.
   * - The class supports operations such as insertion, key lookup, and removal.
   * - The hash function is provided by the user and must be a callable object
   *   that takes a key and returns a hash value.
   *
   * @note This class is not thread-safe.
   */
  template<typename Key, typename Value>
  class hash_map final : public associative_map<Key, Value> {
  public:
    hash_map(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);
    explicit hash_map(const std::function<hash_t(const Key&)>& hash_function);

    virtual void insert(const Key& key, const Value& value) override;
    virtual std::optional<Value> find_by_key(const Key& key) const override;
    virtual void remove(const Key& key) override;

  private:
    using bucket_t = std::vector<std::tuple<Key, Value, hash_t>>;

    const std::function<hash_t(const Key&)> hash_function;
    // TODO: Replace with custom list implementation
    std::vector<bucket_t> buckets;

    const bucket_t& find_bucket_by_key(const Key& key) const;
    bucket_t& find_bucket_by_key(const Key& key);
    void redistribute_buckets(const size_t& new_size);
    [[nodiscard]] double calculate_load_factor() const;
  };

  /**
   * @class hash_multi_map
   * @brief A hash-based associative multi-map implementation.
   *
   * This class provides an efficient hash-based implementation of an associative
   * multi-map, where each key can be associated with multiple values. It uses a
   * hash function to distribute keys into buckets, ensuring average O(1) runtime
   * complexity for insertion, lookup, and removal operations.
   *
   * @tparam Key The type of the keys stored in the map.
   * @tparam Value The type of the values associated with the keys.
   *
   * @details
   * - The multi-map uses a vector of buckets, where each bucket is a vector of
   *   tuples containing the key, value, and the computed hash.
   * - The number of buckets can grow dynamically to maintain a low load factor,
   *   ensuring efficient operations.
   * - The class supports operations such as insertion, key lookup, and removal
   *   of specific key-value pairs or all values associated with a key.
   * - The hash function is provided by the user and must be a callable object
   *   that takes a key and returns a hash value.
   *
   * @note This class is not thread-safe.
   */
  template<typename Key, typename Value>
  class hash_multi_map final : public associative_multi_map<Key, Value> {
  public:
    hash_multi_map(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);
    explicit hash_multi_map(const std::function<hash_t(const Key&)>& hash_function);

    virtual void insert(const Key& key, const Value& value) override;
    virtual bool exists_by_key(const Key& key) const override;
    virtual bool exists(const Key& key, const Value& value) const override;
    virtual void remove_by_key(const Key& key) override;
    virtual void remove(const Key& key, const Value& value) override;

  private:
    using bucket_t = std::vector<std::tuple<Key, Value, hash_t>>;

    const std::function<hash_t(const Key&)> hash_function;
    // TODO: Replace with custom list implementation
    std::vector<bucket_t> buckets;

    const bucket_t& find_bucket_by_key(const Key& key) const;
    bucket_t& find_bucket_by_key(const Key& key);
    void redistribute_buckets(const size_t& new_size);
    [[nodiscard]] double calculate_load_factor() const;
  };
}
