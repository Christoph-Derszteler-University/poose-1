#include "benchmark.hpp"

#include <iostream>
#include <format>

void containers::benchmark::print_benchmark(const std::function<void()>& action, const std::string& name) {
  const auto duration = benchmark_action(action);
  std::cout << std::format("{} took {:.6f} microseconds\n", name, duration.count());
}

std::chrono::duration<double> containers::benchmark::benchmark_action(const std::function<void()>& action) {
  const auto begin = std::chrono::high_resolution_clock::now();
  action();
  const auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
}