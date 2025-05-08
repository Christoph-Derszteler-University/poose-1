#pragma once

#include <functional>
#include <chrono>

namespace containers::benchmark {
  void print_benchmark(
    const std::function<void()>& action,
    const std::string& name,
    const std::string& action_name,
    const int& size
  );
  std::chrono::duration<double> benchmark_action(const std::function<void()>& action);

  void benchmark_with_different_sizes(
    const std::function<void(const int&)>& benchmark,
    const std::vector<int>& sizes
  );
}