#include <iostream>
#include <associative/set/hash_set.hpp>

constexpr std::hash<std::string> hash_function;

int main() {
  auto container = containers::associative::hash_set<std::string>(hash_function);
  std::cout << "exists before inserting: " << container.exists("test") << std::endl;

  container.insert("test");
  container.insert("okay");
  container.insert("test");
  std::cout << " (Container size: " << container.size() << ")" << std::endl;

  // Check twice
  for (auto index = 0; index < 2; ++index) {
    for (const auto& key : container) {
      std::cout << "element in container (iterated): " << key << std::endl;
    }
  }

  container.remove("test");
  std::cout << "exists after removing: " << container.exists("test") << std::endl;
}