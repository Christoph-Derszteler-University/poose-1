#pragma once

#include <functional>
#include <chrono>

namespace containers::benchmark {
  void print_benchmark(const std::function<void()>& action, const std::string& name);
  std::chrono::duration<double> benchmark_action(const std::function<void()>& action);
}