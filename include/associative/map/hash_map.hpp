#pragma once

#include <vector>
#include <functional>
#include <optional>

#include "associative_map.hpp"

namespace containers::associative {
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
}

#include "inline/hash_map.tpp"
