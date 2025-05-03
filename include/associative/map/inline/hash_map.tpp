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
  ) : hash_function(hash_function) {
    const auto bucket_count_log_2 = std::ceil(std::log2(bucket_count));
    buckets(std::vector(
      std::pow(2, bucket_count_log_2),
      std::vector<std::tuple<Key, Value, hash_t>>()
    ));
  }

  template<typename Key, typename Value>
  hash_map<Key, Value>::hash_map(
    const std::function<hash_t(const Key&)>& hash_function
  ) : hash_function(hash_function), buckets(std::vector(1, std::vector<std::tuple<Key, Value, hash_t>>())) {}

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
    bool throw_exception
  ) {
    auto& bucket = find_bucket_by_key(key);
    const auto exists = std::ranges::find_if(bucket, [&key](const std::tuple<Key, Value, hash_t>& tuple) {
      return std::get<0>(tuple) == key;
    });

    if (exists == bucket.end()) {
      bucket.push_back(std::make_tuple(key, value, hash_function(key)));
      container::number_elements++;
    } else if (throw_exception) {
      throw duplicate_key<Key>(key);
    }

    if (calculate_load_factor() >= 0.75) {
      redistribute_buckets(buckets.size() * 2);
    }
  }

  template<typename Key, typename Value>
  std::optional<Value> hash_map<Key, Value>::find_by_key(const Key& key) const {
    auto& bucket = find_bucket_by_key(key);
    const auto it = std::ranges::find_if(bucket, [&key](const auto& other) {
      return std::get<0>(other) == key;
    });
    return it != bucket.end() ? std::optional{std::get<1>(*it)} : std::nullopt;
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
    std::erase_if(bucket, [&key](const auto& tuple) {
      return std::get<0>(tuple) == key;
    });

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets.size() / 2), 1));
    }
  }

  template<typename Key, typename Value>
  typename hash_map<Key, Value>::bucket_t& hash_map<Key, Value>::find_bucket_by_key(
    const Key& key
  ) {
    const auto hash = hash_function(key);
    const auto bucket_index = hash % buckets.size();
    return buckets.at(bucket_index);
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
      / static_cast<double>(buckets.size());
  }

  template<typename Key, typename Value>
  void hash_map<Key, Value>::redistribute_buckets(const size_t& new_size) {
    bucket_t existing;
    for (const auto& bucket : buckets) {
      existing.insert(existing.end(), bucket.begin(), bucket.end());
    }

    buckets = std::vector<bucket_t>(new_size);
    for (const auto& tuple : existing) {
      const auto& key = std::get<0>(tuple);
      const auto& hash = std::get<2>(tuple);
      const auto bucket_index = hash % buckets.size();
      buckets.at(bucket_index).push_back(tuple);
    }
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::begin() {
    const auto first_non_empty = hash_map_iterator<bucket_t, Key, Value>::calculate_next_non_empty_bucket_index(buckets, 0);
    return hash_map_iterator<bucket_t, Key, Value>(std::make_shared<std::vector<bucket_t>>(buckets), first_non_empty, 0);
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::end() {
    return hash_map_iterator<bucket_t, Key, Value>(std::make_shared<std::vector<bucket_t>>(buckets), buckets.size(), 0);
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::cbegin() const {
    const auto first_non_empty = hash_map_iterator<bucket_t, Key, Value>::calculate_next_non_empty_bucket_index(buckets, 0);
    return hash_map_iterator<bucket_t, Key, Value>(std::make_shared<std::vector<bucket_t>>(buckets), first_non_empty, 0);
  }

  template<typename Key, typename Value>
  hash_map_iterator<typename hash_map<Key, Value>::bucket_t, Key, Value> hash_map<Key, Value>::cend() const {
    return hash_map_iterator<bucket_t, Key, Value>(std::make_shared<std::vector<bucket_t>>(buckets), buckets.size(), 0);
  }
}