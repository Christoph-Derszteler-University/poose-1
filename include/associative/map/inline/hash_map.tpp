#pragma once

#include <cmath>
#include <tuple>
#include <algorithm>

#include "associative/map/value_not_found.hpp"
#include "associative/duplicate_key.hpp"

namespace containers::associative {
  template<typename Key, typename Value>
  hash_map<Key, Value>::hash_map(
    const std::function<hash_t(const Key&)>& hash_function,
    const size_t& bucket_count
  ) :
    hash_function(hash_function),
    buckets_ptr(std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>()))
  {
    const auto bucket_count_log_2 = std::ceil(std::log2(bucket_count));
    const auto adjusted_bucket_count = std::pow(2, bucket_count_log_2);
    for (auto index = 0; index < adjusted_bucket_count; ++index) {
      buckets_ptr->push_front(sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>());
    }
  }

  template<typename Key, typename Value>
  hash_map<Key, Value>::hash_map(
    const std::function<hash_t(const Key&)>& hash_function
  ) : hash_function(hash_function),
    buckets_ptr(std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>()))
  {
    buckets_ptr->push_front(sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>());
  }

  template<typename Key, typename Value>
  void hash_map<Key, Value>::insert(const Key& key, const Value& value) {
    insert_with_optional_throw(key, value, true);
  }

  template<typename Key, typename Value>
  void hash_map<Key, Value>::insert_safely(const Key& key, const Value& value) {
    insert_with_optional_throw(key, value, false);
  }

  template<typename Key, typename Value>
  void hash_map<Key, Value>::insert_with_optional_throw(
    const Key& key,
    const Value& value,
    const bool throw_exception
  ) {
    auto& bucket = find_bucket_by_key(key);
    const auto exists = std::ranges::find_if(bucket, [&key](const auto& tuple_pointer) {
      return std::get<0>(tuple_pointer->data) == key;
    });

    if (exists == bucket.end()) {
      bucket.push_back(std::make_tuple(key, value, hash_function(key)));
      container::number_elements++;
    } else if (throw_exception) {
      throw duplicate_key<Key>(key);
    }

    if (calculate_load_factor() >= 0.75) {
      redistribute_buckets(buckets_ptr->size() * 2);
    }
  }

  template<typename Key, typename Value>
  std::optional<Value> hash_map<Key, Value>::find_by_key(const Key& key) const {
    auto& bucket = find_bucket_by_key(key);
    const auto it = std::ranges::find_if(bucket, [&key](const auto& tuple_pointer) {
      return std::get<0>(tuple_pointer->data) == key;
    });
    return it != bucket.end() ? std::optional{std::get<1>((*it)->data)} : std::nullopt;
  }

  template<typename Key, typename Value>
  Value hash_map<Key, Value>::find_by_key_or_throw(const Key& key) const {
    const auto& optional = find_by_key(key);
    if (!optional.has_value()) {
      throw value_not_found<Key>(key);
    }
    return optional.value();
  }

  template<typename Key, typename Value>
  void hash_map<Key, Value>::remove(const Key& key) {
    auto& bucket = find_bucket_by_key(key);
    const auto initial_size = bucket.size();
    for (const auto& tuple_pointer : bucket) {
      if (std::get<0>(tuple_pointer->data) == key) {
        bucket.erase(tuple_pointer);
      }
    }

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets_ptr->size() / 2), 1));
    }
  }

  template<typename Key, typename Value>
  typename hash_map<Key, Value>::bucket_t& hash_map<Key, Value>::find_bucket_by_key(
    const Key& key
  ) {
    const auto hash = hash_function(key);
    const auto bucket_index = hash % buckets_ptr->size();
    return buckets_ptr->at(bucket_index)->data;
  }

  template<typename Key, typename Value>
  const typename hash_map<Key, Value>::bucket_t& hash_map<Key, Value>::find_bucket_by_key(
    const Key& key
  ) const {
    return const_cast<hash_map*>(this)->find_bucket_by_key(key);
  }

  template<typename Key, typename Value>
  double hash_map<Key, Value>::calculate_load_factor() const noexcept {
    return static_cast<double>(container::number_elements)
      / static_cast<double>(buckets_ptr->size());
  }

  template<typename Key, typename Value>
  void hash_map<Key, Value>::redistribute_buckets(const size_t& new_size) {
    bucket_t existing;
    for (const auto& bucket_ptr : *buckets_ptr) {
      for (const auto& element : bucket_ptr->data) {
        existing.push_back(element->data);
      }
    }

    buckets_ptr = std::make_shared<sequential::doubly_linked_list<bucket_t>>(sequential::doubly_linked_list<bucket_t>());
    for (auto index = 0; index < new_size; ++index) {
      buckets_ptr->push_front(sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>());
    }
    for (const auto& tuple_pointer : existing) {
      const auto& tuple = tuple_pointer->data;
      const auto& key = std::get<0>(tuple);
      const auto& hash = std::get<2>(tuple);
      const auto bucket_index = hash % buckets_ptr->size();
      buckets_ptr->at(bucket_index)->data.push_back(tuple);
    }
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::begin() {
    const auto first_non_empty = hash_map_iterator<bucket_t, Key, Value>::calculate_next_non_empty_bucket_index(*buckets_ptr, 0);
    return hash_map_iterator<bucket_t, Key, Value>(buckets_ptr, first_non_empty, 0);
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::end() {
    return hash_map_iterator<bucket_t, Key, Value>(buckets_ptr, buckets_ptr->size(), 0);
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::cbegin() const {
    const auto first_non_empty = hash_map_iterator<bucket_t, Key, Value>::calculate_next_non_empty_bucket_index(*buckets_ptr, 0);
    return hash_map_iterator<bucket_t, Key, Value>(buckets_ptr, first_non_empty, 0);
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::cend() const {
    return hash_map_iterator<bucket_t, Key, Value>(buckets_ptr, buckets_ptr->size(), 0);
  }
}