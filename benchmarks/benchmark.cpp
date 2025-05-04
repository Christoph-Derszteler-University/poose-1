#include "benchmark.hpp"

#include <iostream>
#include <format>

void containers::benchmark::print_benchmark(const std::function<void()>& action, const std::string& name) {
  const auto duration = benchmark_action(action);
  const int microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  std::cout << std::format(
    "{} took {:d} ({:e}) microseconds",
    name,
    microseconds,
    static_cast<double>(microseconds)
  ) << std::endl;
}

std::chrono::duration<double> containers::benchmark::benchmark_action(const std::function<void()>& action) {
  const auto begin = std::chrono::high_resolution_clock::now();
  action();
  const auto end = std::chrono::high_resolution_clock::now();
  return end - begin;
}