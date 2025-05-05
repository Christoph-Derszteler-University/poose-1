#pragma once

#include <memory>

#include "sequential/doubly_linked_list.hpp"

namespace containers::associative {
  template<typename Bucket, typename Key, typename Value>
  class hash_map_iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<Key, Value>;

    hash_map_iterator();
    hash_map_iterator(
      const std::shared_ptr<sequential::doubly_linked_list<Bucket>>& ptr,
      const size_t& outer_index,
      const size_t& inner_index
    );

    value_type operator*() const;

    // Prefix increment
    hash_map_iterator& operator++();
    // Postfix increment
    hash_map_iterator operator++(int);

    bool operator==(const hash_map_iterator& other) const;

    /**
     * @brief Returns the index of the first non-empty bucket with a higher index than the specified one.
     * @return The index of the first non-empty bucket in the doubly linked list.
     * If all buckets are empty, buckets.size() is returned.
    */
    [[nodiscard]] static int calculate_next_non_empty_bucket_index(
      const sequential::doubly_linked_list<Bucket>& buckets,
      const int& base_index
    );
  private:
    std::shared_ptr<sequential::doubly_linked_list<Bucket>> ptr;
    size_t outer_index;
    size_t inner_index;
  };
}

#include "inline/hash_map_iterator.tpp"