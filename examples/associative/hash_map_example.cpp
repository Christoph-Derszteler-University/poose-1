#include <iostream>
#include <associative/map/hash_map.hpp>

constexpr std::hash<std::string> hash_function;

int main() {
  auto container = containers::associative::hash_map<std::string, std::string>(hash_function);
  const auto exists_before = container.find_by_key("test");
  std::cout << "exists before inserting: " << exists_before.has_value() << std::endl;

  container.insert("test", "indeed");
  container.insert("okay", "boomer");
  container.insert_safely("test", "lmao");
  std::cout << "value after inserting: " << container.find_by_key("test").value()
    << " (Container size: " << container.size() << ")" << std::endl;

  try {
    const auto test = container.find_by_key_or_throw("lol");
  } catch (const containers::associative::value_not_found<std::string>& value_not_found) {
    std::cout << value_not_found.what() << std::endl;
  }

  // Check twice
  for (auto index = 0; index < 2; ++index) {
    for (const auto& element : container) {
      std::cout << "element in container (iterated): " << std::get<0>(element) << std::endl;
    }
  }

  container.remove("test");
  const auto exists_remove = container.find_by_key("test");
  std::cout << "exists after removing: " << exists_remove.has_value() << std::endl;
}