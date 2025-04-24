#pragma once

#include <vector>
#include <memory>

namespace containers::associative {
  template<typename Bucket, typename Key>
  class hash_set_iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = Key;

    hash_set_iterator(
      const std::shared_ptr<std::vector<Bucket>>& ptr,
      const size_t& outer_index,
      const size_t& inner_index
    );

    value_type operator*() const;

    // Prefix increment
    hash_set_iterator& operator++();
    // Postfix increment
    hash_set_iterator operator++(int);

    bool operator==(const hash_set_iterator& other) const;

    /**
     * @brief Returns the index of the first non-empty bucket with a higher index than the specified one.
     * @return The index of the first non-empty bucket in the vector.
     * If all buckets are empty, buckets.size() is returned.
    */
    [[nodiscard]] static int calculate_next_non_empty_bucket_index(
      const std::vector<Bucket>& buckets,
      const int& base_index
    );
  private:
    std::shared_ptr<std::vector<Bucket>> ptr;
    size_t outer_index;
    size_t inner_index;
  };

  // TODO: Fix. Assert is never executed
  template<typename Bucket, typename Key>
  struct validate_iterator {
    static_assert(
      std::forward_iterator<hash_set_iterator<Bucket, Key>>,
      "hash_set_iterator must satisfy std::forward_iterator"
    );
  };
}

#include "inline/hash_set_iterator.tpp"