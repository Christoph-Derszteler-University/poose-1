#include <iostream>
#include <associative/map/hash_map.hpp>

constexpr std::hash<std::string> hash_function;

int main() {
  auto container = containers::associative::hash_map<std::string, std::string>(hash_function);
  auto exists_before = container.find_by_key("test");
  std::cout << "exists before inserting: " << exists_before.has_value() << std::endl;

  container.insert("test", "indeed");
  std::cout << "value after inserting: " << container.find_by_key("test").value() << std::endl;

  container.remove("test");
  auto exists_remove = container.find_by_key("test");
  std::cout << "exists after removing: " << exists_remove.has_value() << std::endl;
}