#include <iostream>

#include <associative/map/hash_multi_map.hpp>

constexpr std::hash<std::string> hash_function;

int main() {
  auto container = containers::associative::hash_multi_map<std::string, std::string>(hash_function);
  std::cout << "exists before inserting: " << container.exists_by_key("test") << std::endl;

  container.insert("test", "indeed");
  container.insert("test", "no way");
  container.insert("okay", "boomer");
  std::cout << "value after inserting: " << container.exists("test", "indeed");
  std::cout << " (Container size: " << container.size() << ")" << std::endl;

  for (const auto& element : container) {
    std::cout << "element in container (iterated): " << std::get<0>(element) << ":" << std::get<1>(element) << std::endl;
  }

  container.remove_by_key("test");
  std::cout << "exists after removing: " << container.exists_by_key("test") << std::endl;
}