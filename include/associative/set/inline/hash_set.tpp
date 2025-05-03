#pragma once

#include <cmath>
#include <tuple>
#include <algorithm>

#include "associative/duplicate_key.hpp"

namespace containers::associative {
  template<typename Key>
  hash_set<Key>::hash_set(
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
  hash_set<Key>::hash_set(
    const std::function<hash_t(const Key&)>& hash_function
  ) :
    hash_function(hash_function),
    buckets_ptr(std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>()))
  {
    buckets_ptr->push_front(sequential::doubly_linked_list<std::pair<Key, hash_t>>());
  }

  template<typename Key>
  void hash_set<Key>::insert(const Key& key) {
    insert_with_optional_throw(key, true);
  }

  template<typename Key>
  void hash_set<Key>::insert_safely(const Key& key) {
    insert_with_optional_throw(key, false);
  }

  template<typename Key>
  void hash_set<Key>::insert_with_optional_throw(
    const Key& key,
    const bool throw_exception
  ) {
    auto& bucket = find_bucket_by_key(key);
    const auto exists = std::find_if(
      bucket.begin(),
      bucket.end(),
      [&key](const auto& other_pointer) {
        return std::get<0>(other_pointer->data) == key;
      }
    );

    if (exists == bucket.end()) {
      bucket.push_back(std::make_pair(key, hash_function(key)));
      container::number_elements++;
    } else if (throw_exception) {
      throw duplicate_key<Key>(key);
    }

    if (calculate_load_factor() >= 0.75) {
      redistribute_buckets(buckets_ptr->size() * 2);
    }
  }

  template<typename Key>
  bool hash_set<Key>::exists(const Key& key) const {
    auto& bucket = find_bucket_by_key(key);
    return std::find_if(bucket.begin(), bucket.end(), [&key](const auto& other) {
      return std::get<0>(other->data) == key;
    }) != bucket.end();
  }

  template<typename Key>
  void hash_set<Key>::remove(const Key& key) {
    auto& bucket = find_bucket_by_key(key);
    const auto initial_size = bucket.size();
    for (const auto& pair_pointer : bucket) {
      if (std::get<0>(pair_pointer->data) == key) {
        bucket.erase(pair_pointer);
      }
    }

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets_ptr->size() / 2), 1));
    }
  }

  template<typename Key>
  typename hash_set<Key>::bucket_t& hash_set<Key>::find_bucket_by_key(
    const Key& key
  ) {
    const auto hash = hash_function(key);
    const auto bucket_index = hash % buckets_ptr->size();
    return buckets_ptr->at(bucket_index)->data;
  }

  template<typename Key>
  const typename hash_set<Key>::bucket_t& hash_set<Key>::find_bucket_by_key(
    const Key& key
    ) const {
    return const_cast<hash_set*>(this)->find_bucket_by_key(key);
  }

  template<typename Key>
  double hash_set<Key>::calculate_load_factor() const noexcept {
    return static_cast<double>(container::number_elements)
      / static_cast<double>(buckets_ptr->size());
  }

  template<typename Key>
  void hash_set<Key>::redistribute_buckets(const size_t& new_size) {
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
    for (const auto& pair_pointer : existing) {
      const auto& pair = pair_pointer->data;
      const auto& key = std::get<0>(pair);
      const auto& hash = std::get<1>(pair);
      const auto bucket_index = hash % buckets_ptr->size();
      buckets_ptr->at(bucket_index)->data.push_back(pair);
    }
  }

  template<typename Key>
  hash_set_iterator<typename hash_set<Key>::bucket_t, Key> hash_set<Key>::begin() {
    const auto first_non_empty = hash_set_iterator<bucket_t, Key>::calculate_next_non_empty_bucket_index(*buckets_ptr, 0);
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, first_non_empty, 0);
  }

  template<typename Key>
  hash_set_iterator<typename hash_set<Key>::bucket_t, Key> hash_set<Key>::end() {
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, buckets_ptr->size(), 0);
  }

  template<typename Key>
  hash_set_iterator<typename hash_set<Key>::bucket_t, Key> hash_set<Key>::cbegin() const {
    const auto first_non_empty = hash_set_iterator<bucket_t, Key>::calculate_next_non_empty_bucket_index(*buckets_ptr, 0);
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, first_non_empty, 0);
  }

  template<typename Key>
  hash_set_iterator<typename hash_set<Key>::bucket_t, Key> hash_set<Key>::cend() const {
    return hash_set_iterator<bucket_t, Key>(buckets_ptr, buckets_ptr->size(), 0);
  }
}