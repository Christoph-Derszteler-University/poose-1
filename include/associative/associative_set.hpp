#pragma once

#include <functional>
#include <container.hpp>

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
    virtual bool exists(const Key& key) const = 0;

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
    virtual bool exists(const Key& key) const = 0;

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

  /**
   * @class hash_set
   * @brief A hash-based associative set implementation.
   *
   * This class provides an efficient hash-based implementation of an associative set,
   * where each key is stored uniquely. It uses a hash function to distribute keys
   * into buckets, ensuring average O(1) runtime complexity for insertion, lookup,
   * and removal operations.
   *
   * @tparam Key The type of the keys stored in the set.
   *
   * @details
   * - The set uses a vector of buckets, where each bucket is a vector of key-hash pairs.
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
  class hash_set final : public associative_set<Key> {
  public:
    hash_set(const std::function<hash_t(const Key&)>& hash_function, const size_t& bucket_count);
    explicit hash_set(const std::function<hash_t(const Key&)>& hash_function);

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