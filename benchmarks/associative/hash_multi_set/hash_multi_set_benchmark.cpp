#include <unordered_set>
#include <iostream>
#include <thread>

#include "benchmark.hpp"
#include "associative/set/hash_multi_set.hpp"

constexpr auto hash_function = std::hash<std::string>();
// These sizes take too long with our linked list implementation
// const auto extendedSizes = std::vector{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
const auto sizes = std::vector{1, 10, 100, 1000, 10000, 100000};
auto joined_threads = std::vector<std::thread>();

containers::associative::hash_multi_set<std::string> create_hash_multi_set(const int& size) {
  auto hash_multi_set = containers::associative::hash_multi_set<std::string>(hash_function, size);
  for (int i = 0; i < size; ++i) {
    hash_multi_set.insert(std::to_string(i));
  }
  return hash_multi_set;
}

std::unordered_multiset<std::string> create_unordered_multiset(const int& size) {
  auto unordered_multiset = std::unordered_multiset<std::string>(size, hash_function);
  for (int i = 0; i < size; ++i) {
    unordered_multiset.insert(std::to_string(i));
  }
  return unordered_multiset;
}

void benchmark_hash_multi_set_insert(const int& size) {
  auto hash_multi_set = containers::associative::hash_multi_set<std::string>(hash_function, size);
  containers::benchmark::print_benchmark([&hash_multi_set, &size] {
    for (int i = 0; i < size; ++i) {
      hash_multi_set.insert(std::to_string(i));
    }
  }, "hash_multiset", "hash multiset insert", size);
}

void benchmark_unordered_multiset_insert(const int& size) {
  auto unordered_multiset = std::unordered_multiset<std::string>(size, hash_function);
  containers::benchmark::print_benchmark([&unordered_multiset, &size] {
    for (int i = 0; i < size; ++i) {
      unordered_multiset.insert(std::to_string(i));
    }
  }, "unordered_multiset", "unordered multiset insert", size);
}

void benchmark_insert() {
  std::thread hash_multi_set_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_hash_multi_set_insert, sizes);
  });
  std::thread unordered_multiset_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_unordered_multiset_insert, sizes);
  });
  joined_threads.push_back(std::move(hash_multi_set_thread));
  joined_threads.push_back(std::move(unordered_multiset_thread));
  std::cout << "Started threads for insert-benchmarks" << std::endl;
}

void benchmark_hash_multi_set_exists(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    const auto hash_multi_set = create_hash_multi_set(size);
    for (int index = 0; index < size; ++index) {
      hash_multi_set.exists(std::to_string(index));
    }
  }, "hash_multiset", "hash multiset exists", size);
}

void benchmark_unordered_multiset_exists(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    const auto unordered_multiset = create_unordered_multiset(size);
    for (int index = 0; index < size; ++index) {
      unordered_multiset.contains(std::to_string(index));
    }
  }, "unordered_multiset", "unordered multiset exists", size);
}

void benchmark_exists() {
  std::thread hash_multi_set_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_hash_multi_set_exists, sizes);
  });
  std::thread unordered_multiset_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_unordered_multiset_exists, sizes);
  });
  joined_threads.push_back(std::move(hash_multi_set_thread));
  joined_threads.push_back(std::move(unordered_multiset_thread));
  std::cout << "Started threads for exists-benchmarks" << std::endl;
}

void benchmark_hash_multi_set_remove(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    auto hash_multi_set = create_hash_multi_set(size);
    for (int index = 0; index < size; ++index) {
      hash_multi_set.remove(std::to_string(index));
    }
  }, "hash_multiset", "hash multiset remove", size);
}

void benchmark_unordered_multiset_remove(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    auto unordered_multiset = create_unordered_multiset(size);
    for (int index = 0; index < size; ++index) {
      unordered_multiset.erase(std::to_string(index));
    }
  }, "unordered_multiset", "unordered multiset remove", size);
}

void benchmark_remove() {
  std::thread hash_multi_set_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_hash_multi_set_remove, sizes);
  });
  std::thread unordered_multiset_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_unordered_multiset_remove, sizes);
  });
  joined_threads.push_back(std::move(hash_multi_set_thread));
  joined_threads.push_back(std::move(unordered_multiset_thread));
  std::cout << "Started threads for remove-benchmarks" << std::endl;
}

int main() {
  benchmark_insert();
  benchmark_exists();
  benchmark_remove();

  std::cout << "Waiting for all threads to finish execution..." << std::endl;
  std::ranges::for_each(joined_threads, [](auto& thread) { thread.join(); });
  std::cout << "Waiting for all threads to finish execution..." << std::endl;
}