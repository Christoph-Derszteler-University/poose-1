#pragma once

namespace containers::associative {
  template<typename Bucket, typename Key, typename Value>
  hash_map_iterator<Bucket, Key, Value>::hash_map_iterator()
    : ptr(nullptr), outer_index(0), inner_index(0) {}

  template<typename Bucket, typename Key, typename Value>
  hash_map_iterator<Bucket, Key, Value>::hash_map_iterator(
    const std::shared_ptr<sequential::doubly_linked_list<Bucket>>& ptr,
    const size_t& outer_index,
    const size_t& inner_index
  ) : ptr(ptr), outer_index(outer_index), inner_index(inner_index) {}

  template<typename Bucket, typename Key, typename Value>
  typename hash_map_iterator<Bucket, Key, Value>::value_type hash_map_iterator<Bucket, Key, Value>::operator*() const {
    const auto& tuple = ptr->at(outer_index)->data.at(inner_index)->data;
    return std::make_pair(std::get<0>(tuple), std::get<1>(tuple));
  }

  template<typename Bucket, typename Key, typename Value>
  hash_map_iterator<Bucket, Key, Value>& hash_map_iterator<Bucket, Key, Value>::operator++() {
    const auto new_inner_index = inner_index + 1;
    if (new_inner_index >= ptr->at(outer_index)->data.size()) {
      const auto new_outer_index = calculate_next_non_empty_bucket_index(*ptr, outer_index);

      inner_index = 0;
      outer_index = new_outer_index >= ptr->size() ? ptr->size() : new_outer_index;
      return *this;
    }
    inner_index = new_inner_index;
    return *this;
  }

  template<typename Bucket, typename Key, typename Value>
  hash_map_iterator<Bucket, Key, Value> hash_map_iterator<Bucket, Key, Value>::operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
  }

  template<typename Bucket, typename Key, typename Value>
  bool hash_map_iterator<Bucket, Key, Value>::operator==(const hash_map_iterator& other) const {
    return ptr == other.ptr
      && outer_index == other.outer_index
      && inner_index == other.inner_index;
  }

  template<typename Bucket, typename Key, typename Value>
  int hash_map_iterator<Bucket, Key, Value>::calculate_next_non_empty_bucket_index(
    const sequential::doubly_linked_list<Bucket>& buckets,
    const int& base_index
  ) {
    auto first_non_empty = buckets.size();

    for (size_t index = base_index + 1; index < buckets.size(); ++index) {
      if (!buckets.at(index)->data.empty()) {
        first_non_empty = index;
        break;
      }
    }
    return first_non_empty;
  }
}