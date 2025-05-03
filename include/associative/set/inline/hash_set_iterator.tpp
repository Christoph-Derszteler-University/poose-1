#pragma once


namespace containers::associative {
  template<typename Bucket, typename Key>
  hash_set_iterator<Bucket, Key>::hash_set_iterator()
    : ptr(nullptr), outer_index(0), inner_index(0) {}

  template<typename Bucket, typename Key>
  hash_set_iterator<Bucket, Key>::hash_set_iterator(
    const std::shared_ptr<sequential::doubly_linked_list<Bucket>>& ptr,
    const size_t& outer_index,
    const size_t& inner_index
  ) : ptr(ptr), outer_index(outer_index), inner_index(inner_index) {}

  template<typename Bucket, typename Key>
  typename hash_set_iterator<Bucket, Key>::value_type hash_set_iterator<Bucket, Key>::operator*() const {
    const auto& pair = ptr->at(outer_index)->data.at(inner_index)->data;
    return std::get<0>(pair);
  }

  template<typename Bucket, typename Key>
  hash_set_iterator<Bucket, Key>& hash_set_iterator<Bucket, Key>::operator++() {
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

  template<typename Bucket, typename Key>
  hash_set_iterator<Bucket, Key> hash_set_iterator<Bucket, Key>::operator++(int) {
    auto tmp = *this;
    ++*this;
    return tmp;
  }

  template<typename Bucket, typename Key>
  bool hash_set_iterator<Bucket, Key>::operator==(const hash_set_iterator& other) const {
    return ptr == other.ptr
      && outer_index == other.outer_index
      && inner_index == other.inner_index;
  }

  template<typename Bucket, typename Key>
  int hash_set_iterator<Bucket, Key>::calculate_next_non_empty_bucket_index(
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