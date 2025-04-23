#pragma once

#include <functional>

#include "associative_multi_set.hpp"

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
  public:
    hash_multi_set(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);
    explicit hash_multi_set(const std::function<hash_t(const Key&)>& hash_function);

    virtual void insert(const Key& key) override;
    virtual bool exists(const Key& key) const override;
    virtual void remove(const Key& key) override;

  private:
    using bucket_t = std::vector<std::pair<Key, hash_t>>;

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
