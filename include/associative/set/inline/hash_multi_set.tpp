#pragma once

#include <cmath>
#include <tuple>
#include <algorithm>

namespace containers::associative {
  template<typename Key>
  hash_multi_set<Key>::hash_multi_set(
    const std::function<hash_t(const Key&)>& hash_function,
    const size_t& bucket_count
  ) :
    hash_function(hash_function),
    buckets_ptr(std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>()))
  {
    const auto bucket_count_log_2 = std::ceil(std::log2(bucket_count));
    const auto adjusted_bucket_count = std::pow(2, bucket_count_log_2);
    for (auto index = 0; index < adjusted_bucket_count; ++index) {
      buckets_ptr->push_front(sequential::doubly_linked_list<std::pair<Key, hash_t>>());
    }
  }

  template<typename Key>
  hash_multi_set<Key>::hash_multi_set(
    const std::function<hash_t(const Key&)>& hash_function
  ) :
    hash_function(hash_function),
    buckets_ptr(std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>()))
  {
    buckets_ptr->push_front(sequential::doubly_linked_list<std::pair<Key, hash_t>>());
  }

  template<typename Key>
  void hash_multi_set<Key>::insert(const Key& key) {
    auto& bucket = find_bucket_by_key(key);
    bucket.push_back(std::make_pair(key, hash_function(key)));

    if (calculate_load_factor() >= 0.75) {
      redistribute_buckets(buckets_ptr->size() * 2);
    }
    container::number_elements++;
  }

  template<typename Key>
  bool hash_multi_set<Key>::exists(const Key& key) const {
    auto& bucket = find_bucket_by_key(key);
    return std::ranges::find_if(bucket, [&key](const auto& other) {
      return std::get<0>(other->data) == key;
    }) != bucket.end();
  }

  template<typename Key>
  void hash_multi_set<Key>::remove(const Key& key) {
    auto& bucket = find_bucket_by_key(key);
    const auto initial_size = bucket.size();
    auto to_remove = sequential::doubly_linked_list<typename sequential::abstract_doubly_linked_list<std::pair<Key, hash_t>>::node_t>{};
    for (const auto& pair_pointer : bucket) {
      if (std::get<0>(pair_pointer->data) == key) {
        to_remove.push_back(pair_pointer);
      }
    }
    for (const auto& pair_pointer : to_remove) {
      bucket.erase(pair_pointer->data);
    }

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets_ptr->size() / 2), 1));
    }
  }

  template<typename Key>
  typename hash_multi_set<Key>::bucket_t& hash_multi_set<Key>::find_bucket_by_key(
    const Key& key
  ) {
    const auto hash = hash_function(key);
    const auto bucket_index = hash % buckets_ptr->size();
    return buckets_ptr->at(bucket_index)->data;
  }

  template<typename Key>
  const typename hash_multi_set<Key>::bucket_t& hash_multi_set<Key>::find_bucket_by_key(
    const Key& key
    ) const {
    return const_cast<hash_multi_set*>(this)->find_bucket_by_key(key);
  }

  template<typename Key>
  double hash_multi_set<Key>::calculate_load_factor() const noexcept {
    return static_cast<double>(container::number_elements)
      / static_cast<double>(buckets_ptr->size());
  }

  template<typename Key>
  void hash_multi_set<Key>::redistribute_buckets(const size_t& new_size) {
    bucket_t existing;
    for (const auto& bucket_ptr : *buckets_ptr) {
      for (const auto& element : bucket_ptr->data) {
        existing.push_back(element->data);
      }
    }

    buckets_ptr = std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>());
    for (auto index = 0; index < new_size; ++index) {
      buckets_ptr->push_front(sequential::doubly_linked_list<std::pair<Key, hash_t>>());
    }
    for (const auto& pair_tuple : existing) {
      const auto& pair = pair_tuple->data;
      const auto& key = std::get<0>(pair);
      const auto& hash = std::get<1>(pair);
      const auto bucket_index = hash % buckets_ptr->size();
      buckets_ptr->at(bucket_index)->data.push_back(pair);
    }
  }

  template<typename Key>
  hash_set_iterator<typename hash_multi_set<Key>::bucket_t, Key> hash_multi_set<Key>::begin() {
    const auto first_non_empty = hash_set_iterator<bucket_t, Key>::calculate_next_non_empty_bucket_index(*buckets_ptr, 0);
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, first_non_empty, 0);
  }

  template<typename Key>
  hash_set_iterator<typename hash_multi_set<Key>::bucket_t, Key> hash_multi_set<Key>::end() {
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, buckets_ptr->size(), 0);
  }

  template<typename Key>
  hash_set_iterator<typename hash_multi_set<Key>::bucket_t, Key> hash_multi_set<Key>::cbegin() const {
    const auto first_non_empty = hash_set_iterator<bucket_t, Key>::calculate_next_non_empty_bucket_index(*buckets_ptr, 0);
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, first_non_empty, 0);
  }

  template<typename Key>
  hash_set_iterator<typename hash_multi_set<Key>::bucket_t, Key> hash_multi_set<Key>::cend() const {
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, buckets_ptr->size(), 0);
  }
}