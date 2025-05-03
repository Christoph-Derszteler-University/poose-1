#pragma once

#include <cmath>
#include <tuple>
#include <algorithm>

namespace containers::associative {
  template<typename Key, typename Value>
  hash_multi_map<Key, Value>::hash_multi_map(
    const std::function<hash_t(const Key&)>& hash_function,
    const size_t& bucket_count
  ) : hash_function(hash_function) {
    const auto bucket_count_log_2 = std::ceil(std::log2(bucket_count));
    const auto adjusted_bucket_count = std::pow(2, bucket_count_log_2);
    for (auto index = 0; index < adjusted_bucket_count; ++index) {
      buckets.push_front(sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>());
    }
  }

  template<typename Key, typename Value>
  hash_multi_map<Key, Value>::hash_multi_map(
    const std::function<hash_t(const Key&)>& hash_function
  ) : hash_function(hash_function), buckets(sequential::doubly_linked_list<bucket_t>()) {
    buckets.push_front(sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>());
  }

  template<typename Key, typename Value>
  void hash_multi_map<Key, Value>::insert(const Key& key, const Value& value) {
    auto& bucket = find_bucket_by_key(key);
    bucket.push_back(std::make_tuple(key, value, hash_function(key)));

    if (calculate_load_factor() >= 0.75) {
      redistribute_buckets(buckets.size() * 2);
    }
    container::number_elements++;
  }

  template<typename Key, typename Value>
  bool hash_multi_map<Key, Value>::exists_by_key(const Key& key) const {
    auto& bucket = find_bucket_by_key(key);
    return std::find_if(bucket.begin(), bucket.end(), [&key](const auto& other) {
      return std::get<0>(other->data) == key;
    }) != bucket.end();
  }

  template<typename Key, typename Value>
  bool hash_multi_map<Key, Value>::exists(const Key& key, const Value& value) const {
    auto& bucket = find_bucket_by_key(key);
    return std::find_if(bucket.begin(), bucket.end(), [&key, &value](const auto& other) {
      return std::get<0>(other->data) == key && std::get<1>(other->data) == value;
    }) != bucket.end();
  }

  template<typename Key, typename Value>
  void hash_multi_map<Key, Value>::remove_by_key(const Key& key) {
    auto& bucket = find_bucket_by_key(key);
    const auto initial_size = bucket.size();
    auto to_remove = sequential::doubly_linked_list<typename sequential::abstract_doubly_linked_list<std::tuple<Key, Value, hash_t>>::node_t>{};
    for (const auto& tuple_pointer : bucket) {
      if (std::get<0>(tuple_pointer->data) == key) {
        to_remove.push_back(tuple_pointer);
      }
    }
    for (const auto& tuple_pointer : to_remove) {
      bucket.erase(tuple_pointer->data);
    }

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets.size() / 2), 1));
    }
  }

  template<typename Key, typename Value>
  void hash_multi_map<Key, Value>::remove(const Key& key, const Value& value) {
    auto& bucket = find_bucket_by_key(key);
    const auto initial_size = bucket.size();
    for (const auto& tuple_pointer : bucket) {
      if (std::get<0>(tuple_pointer->data) == key
        && std::get<1>(tuple_pointer->data) == value
      ) {
        bucket.erase(tuple_pointer);
      }
    }

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets.size() / 2), 1));
    }
  }

  template<typename Key, typename Value>
  typename hash_multi_map<Key, Value>::bucket_t& hash_multi_map<Key, Value>::find_bucket_by_key(
    const Key& key
  ) {
    const auto hash = hash_function(key);
    const auto bucket_index = hash % buckets.size();
    return buckets.at(bucket_index)->data;
  }

  template<typename Key, typename Value>
  const typename hash_multi_map<Key, Value>::bucket_t& hash_multi_map<Key, Value>::find_bucket_by_key(
    const Key& key
    ) const {
    return const_cast<hash_multi_map*>(this)->find_bucket_by_key(key);
  }

  template<typename Key, typename Value>
  double hash_multi_map<Key, Value>::calculate_load_factor() const noexcept {
    return static_cast<double>(container::number_elements)
      / static_cast<double>(buckets.size());
  }

  template<typename Key, typename Value>
  void hash_multi_map<Key, Value>::redistribute_buckets(const size_t& new_size) {
    bucket_t existing;
    for (const auto& bucket_ptr : buckets) {
      for (const auto& element : bucket_ptr->data) {
        existing.push_back(element->data);
      }
    }

    buckets = sequential::doubly_linked_list<bucket_t>();
    for (auto index = 0; index < new_size; ++index) {
      buckets.push_front(sequential::doubly_linked_list<std::tuple<Key, Value, hash_t>>());
    }
    for (const auto& tuple_pointer : existing) {
      const auto& tuple = tuple_pointer->data;
      const auto& key = std::get<0>(tuple);
      const auto& hash = std::get<2>(tuple);
      const auto bucket_index = hash % buckets.size();
      buckets.at(bucket_index)->data.push_back(tuple);
    }
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_multi_map<Key, Value>::bucket_t, Key, Value> hash_multi_map<Key, Value>::begin() {
    const auto first_non_empty = hash_map_iterator<bucket_t, Key, Value>::calculate_next_non_empty_bucket_index(buckets, 0);
    return hash_map_iterator<bucket_t, Key, Value>(
      std::make_shared<sequential::doubly_linked_list<bucket_t>>(buckets),
      first_non_empty,
      0
    );
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_multi_map<Key, Value>::bucket_t, Key, Value> hash_multi_map<Key, Value>::end() {
    return hash_map_iterator<bucket_t, Key, Value>(
      std::make_shared<sequential::doubly_linked_list<bucket_t>>(buckets),
      buckets.size(),
      0
    );
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_multi_map<Key, Value>::bucket_t, Key, Value> hash_multi_map<Key, Value>::cbegin() const {
    const auto first_non_empty = hash_map_iterator<bucket_t, Key, Value>::calculate_next_non_empty_bucket_index(buckets, 0);
    return hash_map_iterator<bucket_t, Key, Value>(
      std::make_shared<sequential::doubly_linked_list<bucket_t>>(buckets),
      first_non_empty,
      0
    );
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_multi_map<Key, Value>::bucket_t, Key, Value> hash_multi_map<Key, Value>::cend() const {
    return hash_map_iterator<bucket_t, Key, Value>(
      std::make_shared<sequential::doubly_linked_list<bucket_t>>(buckets),
      buckets.size(),
      0
    );
  }
}