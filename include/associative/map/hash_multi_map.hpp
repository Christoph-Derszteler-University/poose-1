#pragma once

#include <vector>
#include <functional>

#include "associative_multi_map.hpp"
#include "hash_map_iterator.hpp"

namespace containers::associative {
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
  protected:
    using bucket_t = std::vector<std::tuple<Key, Value, hash_t>>;

  public:
    /**
     * @brief Constructs a hash_multi_map with a custom hash function and a specified number of buckets.
     *
     * @param hash_function A callable object that computes the hash of a given key.
     * @param bucket_count The initial number of buckets in the hash multi-map.
     *
     * @details The number of buckets is adjusted to the nearest power of 2 greater than or equal to `bucket_count`.
     */
    hash_multi_map(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);
    /**
     * @brief Constructs a hash_multi_map with a custom hash function and a single bucket.
     *
     * @param hash_function A callable object that computes the hash of a given key.
     *
     * @details This constructor initializes the hash multi-map with a single bucket, suitable for small datasets.
     */
    explicit hash_multi_map(const std::function<hash_t(const Key&)>& hash_function);

    //! @copydoc associative_multi_map::insert
    virtual void insert(const Key& key, const Value& value) override;
    //! @copydoc associative_multi_map::exists_by_key
    virtual bool exists_by_key(const Key& key) const override;
    //! @copydoc associative_multi_map::exists
    virtual bool exists(const Key& key, const Value& value) const override;
    //! @copydoc associative_multi_map::remove_by_key
    virtual void remove_by_key(const Key& key) override;
    //! @copydoc associative_multi_map::remove
    virtual void remove(const Key& key, const Value& value) override;

    hash_map_iterator<bucket_t, Key, Value> begin();
    hash_map_iterator<bucket_t, Key, Value> end();
    hash_map_iterator<bucket_t, Key, Value> cbegin() const;
    hash_map_iterator<bucket_t, Key, Value> cend() const;
  private:
    const std::function<hash_t(const Key&)> hash_function;
    // TODO: Replace with custom list implementation
    std::vector<bucket_t> buckets;

    const bucket_t& find_bucket_by_key(const Key& key) const;
    bucket_t& find_bucket_by_key(const Key& key);
    void redistribute_buckets(const size_t& new_size);
    [[nodiscard]] double calculate_load_factor() const noexcept;
  };
}

#include "inline/hash_multi_map.tpp"