#pragma once

#include <functional>
#include <optional>

#include "associative_map.hpp"
#include "hash_map_iterator.hpp"
#include "sequential/doubly_linked_list.hpp"

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
   * - The map uses a doubly linked list of buckets, where each bucket is
   *   a doubly linked list of tuples containing the key, value, and the computed hash.
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
  protected:
    using bucket_t = sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>;

  public:
    /**
     * @brief Constructs a hash_map with a custom hash function and a specified number of buckets.
     *
     * @param hash_function A callable object that computes the hash of a given key.
     * @param bucket_count The initial number of buckets in the hash map.
     *
     * @details The number of buckets is adjusted to the nearest power of 2 greater than or equal to `bucket_count`.
     */
    hash_map(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);
    /**
     * @brief Constructs a hash_map with a custom hash function and a single bucket.
     *
     * @param hash_function A callable object that computes the hash of a given key.
     *
     * @details This constructor initializes the hash map with a single bucket, suitable for small datasets.
     */
    explicit hash_map(const std::function<hash_t(const Key&)>& hash_function);

    //! @copydoc associative_map::insert
    virtual void insert(const Key& key, const Value& value) override;
    //! @copydoc associative_map::insert_safely
    virtual void insert_safely(const Key& key, const Value& value) override;
    //! @copydoc associative_map::find_by_key
    virtual std::optional<Value> find_by_key(const Key& key) const override;
    //! @copydoc associative_map::find_by_key_or_throw
    virtual Value find_by_key_or_throw(const Key& key) const override;
    //! @copydoc associative_map::remove
    virtual void remove(const Key& key) override;

    hash_map_iterator<bucket_t, Key, Value> begin();
    hash_map_iterator<bucket_t, Key, Value> end();
    hash_map_iterator<bucket_t, Key, Value> cbegin() const;
    hash_map_iterator<bucket_t, Key, Value> cend() const;

  private:
    const std::function<hash_t(const Key&)> hash_function;
    sequential::doubly_linked_list<bucket_t> buckets;

    void insert_with_optional_throw(
      const Key& key,
      const Value& value,
      bool throw_exception
    );

    [[nodiscard]] const bucket_t& find_bucket_by_key(const Key& key) const;
    [[nodiscard]] bucket_t& find_bucket_by_key(const Key& key);
    void redistribute_buckets(const size_t& new_size);
    [[nodiscard]] double calculate_load_factor() const noexcept;
  };
}

#include "inline/hash_map.tpp"