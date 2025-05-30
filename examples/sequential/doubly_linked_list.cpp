#include <iostream>
#include <sequential/doubly_linked_list.hpp>

int main() {
  containers::sequential::doubly_linked_list<int> list;

  // 10 -> 5 -> 200 -> 500
  list.push_front(5);
  list.push_front(10);
  list.push_back(200);
  list.push_back(500);

  // 10 -> 5 -> 200
  list.pop_back();

  auto five = list.at(1);
  std::cout << five->data << std::endl;

  // 10 -> 5 -> 1000 -> 200
  list.insert(list.back(), 1000);

  std::cout << list.size() << std::endl;

  // 10 -> 5 -> 1000
  list.erase(list.back());

  std::cout << list.size() << std::endl;

  for (const auto &node : list) {
    std::cout << node->data << " ";
  }
}
