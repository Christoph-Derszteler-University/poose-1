#pragma once

#include <functional>

#include "associative_multi_set.hpp"
#include "hash_set_iterator.hpp"

namespace containers::associative {
  /**
   * @class hash_multi_set
   * @brief A hash-based associative multi-set implementation.
   *
   * This class provides an efficient hash-based implementation of an associative
   * multi-set, where each key can be stored multiple times. It uses a hash function
   * to distribute keys into buckets, ensuring average O(1) runtime complexity for
   * insertion, lookup, and removal operations.
   *
   * @tparam Key The type of the keys stored in the multi-set.
   *
   * @details
   * - The multi-set uses a vector of buckets, where each bucket is a vector of key-hash pairs.
   * - The number of buckets grows dynamically to maintain a low load factor, ensuring
   *   efficient operations.
   * - The class supports operations such as insertion, key lookup, and removal.
   * - The hash function is provided by the user and must be a callable object
   *   that takes a key and returns a hash value.
   * - The load factor is used to determine when to resize the bucket vector.
   *   - Buckets are resized when the load factor exceeds 0.75 (grow) or drops below 0.25 (shrink).
   *
   * @note This class is not thread-safe.
   */
  template<typename Key>
  class hash_multi_set final : public associative_multi_set<Key> {
  protected:
    using bucket_t = std::vector<std::pair<Key, hash_t>>;

  public:
    /**
     * @brief Constructs a hash_multi_set with a custom hash function and a specified number of buckets.
     *
     * @param hash_function A callable object that computes the hash of a given key.
     * @param bucket_count The initial number of buckets in the hash multi-set.
     *
     * @details The number of buckets is adjusted to the nearest power of 2 greater than or equal to `bucket_count`.
     */
    hash_multi_set(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);

    /**
     * @brief Constructs a hash_multi_set with a custom hash function and a single bucket.
     *
     * @param hash_function A callable object that computes the hash of a given key.
     *
     * @details This constructor initializes the hash multi-set with a single bucket, suitable for small datasets.
     */
    explicit hash_multi_set(const std::function<hash_t(const Key&)>& hash_function);

    //! @copydoc associative_multi_set::insert
    virtual void insert(const Key& key) override;
    //! @copydoc associative_multi_set::exists
    virtual bool exists(const Key& key) const override;
    //! @copydoc associative_multi_set::remove
    virtual void remove(const Key& key) override;

    hash_set_iterator<bucket_t, Key> begin();
    hash_set_iterator<bucket_t, Key> end();
    hash_set_iterator<bucket_t, Key> cbegin() const;
    hash_set_iterator<bucket_t, Key> cend() const;

  private:
    const std::function<hash_t(const Key&)> hash_function;
    // TODO: Replace with custom list implementation
    std::vector<bucket_t> buckets;

    const bucket_t& find_bucket_by_key(const Key& key) const;
    bucket_t& find_bucket_by_key(const Key& key);
    void redistribute_buckets(const size_t& new_size);
    [[nodiscard]] double calculate_load_factor() const;
  };
}

#include "inline/hash_multi_set.tpp"