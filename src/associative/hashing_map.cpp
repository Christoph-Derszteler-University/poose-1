#include "associative/associative_map.hpp"

#include <cmath>

namespace containers::associative {
  template<typename Key, typename Value>
  hashing_map<Key, Value>::hashing_map(
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
  hashing_map<Key, Value>::hashing_map(
    const std::function<hash_t(const Key&)>& hash_function
  ) : hash_function(hash_function), buckets(std::vector(1, std::vector<std::tuple<Key, Value, hash_t>>())) {}



  template<typename Key, typename Value>
  void hashing_map<Key, Value>::insert(const Key& key, const Value& value) {
    // TODO
  }


  template<typename Key, typename Value>
  typename hashing_map<Key, Value>::bucket_t hashing_map<Key, Value>::find_bucket_by_key(const Key& key) const {
    const auto hash = hash_function(key);
    const auto listIndex = hash % buckets.size();
    return buckets.at(listIndex);
  }

  // TODO: Implementation hashing map
}