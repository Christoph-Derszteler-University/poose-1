#include <unordered_map>
#include <iostream>
#include <thread>

#include "benchmark.hpp"
#include "associative/map/hash_map.hpp"

constexpr auto hash_function = std::hash<std::string>();
// These sizes take too long with our linked list implementation
// const auto extendedSizes = std::vector{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
const auto sizes = std::vector{1, 10, 100, 1000, 10000, 100000};
auto joined_threads = std::vector<std::thread>();

containers::associative::hash_map<std::string, int> create_hash_map(const int& size) {
  auto hash_map = containers::associative::hash_map<std::string, int>(hash_function, size);
  for (int i = 0; i < size; ++i) {
    hash_map.insert(std::to_string(i), i);
  }
  return hash_map;
}

std::unordered_map<std::string, int> create_unordered_map(const int& size) {
  auto unordered_map = std::unordered_map<std::string, int>(size, hash_function);
  for (int i = 0; i < size; ++i) {
    unordered_map.insert({std::to_string(i), i});
  }
  return unordered_map;
}

void benchmark_hash_map_insert(const int& size) {
  auto hash_map = containers::associative::hash_map<std::string, int>(hash_function, size);
  containers::benchmark::print_benchmark([&hash_map, &size] {
    for (int i = 0; i < size; ++i) {
      hash_map.insert(std::to_string(i), i);
    }
  }, "hash_map", "hash map insert", size);
}

void benchmark_unordered_map_insert(const int& size) {
  auto unordered_map = std::unordered_map<std::string, int>(size, hash_function);
  containers::benchmark::print_benchmark([&unordered_map, &size] {
    for (int i = 0; i < size; ++i) {
      unordered_map.insert({std::to_string(i), i});
    }
  }, "unordered_map", "unordered map insert", size);
}

void benchmark_insert() {
  std::thread hash_map_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_hash_map_insert, sizes);
  });
  std::thread unordered_map_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_unordered_map_insert, sizes);
  });
  joined_threads.push_back(std::move(hash_map_thread));
  joined_threads.push_back(std::move(unordered_map_thread));
  std::cout << "Started threads for insert-benchmarks" << std::endl;
}

void benchmark_hash_map_find(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    const auto hash_map = create_hash_map(size);
    for (int index = 0; index < size; ++index) {
      hash_map.find_by_key_or_throw(std::to_string(index));
    }
  }, "hash_map", "hash map find_by_key", size);
}

void benchmark_unordered_map_find(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    const auto unordered_map = create_unordered_map(size);
    for (int index = 0; index < size; ++index) {
      unordered_map.find(std::to_string(index));
    }
  }, "unordered_map", "unordered map find_by_key", size);
}

void benchmark_find() {
  std::thread hash_map_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_hash_map_find, sizes);
  });
  std::thread unordered_map_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_unordered_map_find, sizes);
  });
  joined_threads.push_back(std::move(hash_map_thread));
  joined_threads.push_back(std::move(unordered_map_thread));
  std::cout << "Started threads for find-benchmarks" << std::endl;
}

void benchmark_hash_map_remove(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    auto hash_map = create_hash_map(size);
    for (int index = 0; index < size; ++index) {
      hash_map.remove(std::to_string(index));
    }
  }, "hash_map", "hash map remove", size);
}

void benchmark_unordered_map_remove(const int& size) {
  containers::benchmark::print_benchmark([&size] {
    auto unordered_map = create_unordered_map(size);
    for (int index = 0; index < size; ++index) {
      unordered_map.erase(std::to_string(index));
    }
  }, "unordered_map", "unordered map remove", size);
}

void benchmark_remove() {
  std::thread hash_map_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_hash_map_remove, sizes);
  });
  std::thread unordered_map_thread([] {
    containers::benchmark::benchmark_with_different_sizes(benchmark_unordered_map_remove, sizes);
  });
  joined_threads.push_back(std::move(hash_map_thread));
  joined_threads.push_back(std::move(unordered_map_thread));
  std::cout << "Started threads for remove-benchmarks" << std::endl;
}

int main() {
  benchmark_insert();
  benchmark_find();
  benchmark_remove();

  std::cout << "Waiting for all threads to finish execution..." << std::endl;
  std::ranges::for_each(joined_threads, [](auto& thread) { thread.join(); });
  std::cout << "Waiting for all threads to finish execution..." << std::endl;
}