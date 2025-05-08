#include <vector>
#include <random>
#include <thread>

#include "sequential/priority_queue.hpp"
#include "benchmark.hpp"

const auto N_SIZES = std::vector{1000,2000,3000,4000,5000,6000,7000,8000,9000, 10000};

void benchmark_pq_push(int size) {
  // Initialize test data with size, mt19923 and even distribution
  std::vector<int> data(size);
  std::mt19937_64 rng(123);
  std::uniform_int_distribution<int> dist(0, size);
  for (auto& x : data) x = dist(rng);

  // Measure insertation into the PQ
  containers::benchmark::print_benchmark([&](){
    containers::sequential::priority_queue<int> pq;
    for (int v : data) {
      pq.push(v);
    }
  }, "priority_queue", "push", size);
}

void benchmark_pq_pop(int size) {
  // Initialize PQ with an amount of "size" values for testing
  std::vector<int> data(size);
  std::iota(data.begin(), data.end(), 0);
  containers::sequential::priority_queue<int> pq;
  for (int v : data) {
    pq.push(v);
  }
  // Benchmark
  containers::benchmark::print_benchmark([&](){
    while (!pq.empty()) {
      pq.pop();
    }
  }, "priority_queue", "pop", size);
}

int main() {
  // Parallel benchmark testing to reduce time
  std::thread t1([]{ containers::benchmark::benchmark_with_different_sizes(benchmark_pq_push, N_SIZES); });
  std::thread t2([]{ containers::benchmark::benchmark_with_different_sizes(benchmark_pq_pop, N_SIZES); });
  t1.join();
  t2.join();
  return 0;
}
