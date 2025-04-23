#pragma once

#include <cmath>
#include <tuple>
#include <algorithm>

namespace containers::associative {
  template<typename Key>
  hash_set<Key>::hash_set(
    const std::function<hash_t(const Key&)>& hash_function,
    const size_t& bucket_count
  ) : hash_function(hash_function) {
    const auto bucket_count_log_2 = std::ceil(std::log2(bucket_count));
    buckets(std::vector(
      std::pow(2, bucket_count_log_2),
      std::vector<std::pair<Key, hash_t>>()
    ));
  }

  template<typename Key>
  hash_set<Key>::hash_set(
    const std::function<hash_t(const Key&)>& hash_function
  ) : hash_function(hash_function), buckets(std::vector(1, std::vector<std::pair<Key, hash_t>>())) {}

  template<typename Key>
  void hash_set<Key>::insert(const Key& key) {
    container::number_elements++;
    if (calculate_load_factor() >= 0.75) {
      redistribute_buckets(buckets.size() * 2);
    }

    auto& bucket = find_bucket_by_key(key);
    const auto exists = std::find_if(
      bucket.begin(),
      bucket.end(),
      [&key](const std::pair<Key, hash_t>& value) {
        return std::get<0>(value) == key;
      }
    );

    if (exists == bucket.end()) {
      bucket.push_back(std::make_pair(key, hash_function(key)));
    }
  }

  template<typename Key>
  bool hash_set<Key>::exists(const Key& key) const {
    auto& bucket = find_bucket_by_key(key);
    return std::find_if(bucket.begin(), bucket.end(), [&key](const auto& other) {
      return std::get<0>(other) == key;
    }) != bucket.end();
  }

  template<typename Key>
  void hash_set<Key>::remove(const Key& key) {
    auto& bucket = find_bucket_by_key(key);
    const auto initial_size = bucket.size();
    std::erase_if(bucket, [&key](const auto& pair) {
      return std::get<0>(pair) == key;
    });

    container::number_elements -= initial_size - bucket.size();
    if (calculate_load_factor() <= 0.25) {
      redistribute_buckets(std::max(static_cast<int>(buckets.size() / 2), 1));
    }
  }

  template<typename Key>
  typename hash_set<Key>::bucket_t& hash_set<Key>::find_bucket_by_key(
    const Key& key
  ) {
    const auto hash = hash_function(key);
    const auto bucket_index = hash % buckets.size();
    return buckets.at(bucket_index);
  }

  template<typename Key>
  const typename hash_set<Key>::bucket_t& hash_set<Key>::find_bucket_by_key(
    const Key& key
    ) const {
    return const_cast<hash_set*>(this)->find_bucket_by_key(key);
  }

  template<typename Key>
  double hash_set<Key>::calculate_load_factor() const {
    return static_cast<double>(container::number_elements)
      / static_cast<double>(buckets.size());
  }

  template<typename Key>
  void hash_set<Key>::redistribute_buckets(const size_t& new_size) {
    bucket_t existing;
    for (const auto& bucket : buckets) {
      existing.insert(existing.end(), bucket.begin(), bucket.end());
    }

    buckets = std::vector<bucket_t>(new_size);
    for (const auto& pair : existing) {
      const auto& key = std::get<0>(pair);
      const auto& hash = std::get<1>(pair);
      const auto bucket_index = hash % buckets.size();
      buckets.at(bucket_index).push_back(pair);
    }
  }
}