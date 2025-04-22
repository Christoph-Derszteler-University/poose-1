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

  // TODO: Implementation hashing map


  template<typename Key, typename Value>
  hashing_multi_map<Key, Value>::hashing_multi_map(
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
  hashing_multi_map<Key, Value>::hashing_multi_map(
    const std::function<hash_t(const Key&)>& hash_function
  ) : hash_function(hash_function) {

  }

  // TODO: Implementation hashing multi map
}
