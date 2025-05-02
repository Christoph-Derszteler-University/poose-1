#include <iostream>
#include <sequential/doubly_linked_list.hpp>

int main() {
  containers::sequential::doubly_linked_list<int> list;

  // 10 -> 5 -> 200 -> 500
  list.push_front(5);
  list.push_front(10);
  list.push_back(200);
  list.push_back(500);

  // 10 -> 5
  // list.pop_back();

  auto ten = list.at(4);
  // 1000 -> 10 -> 5
  // list.insert(ten, 1000);

  std::cout << ten << std::endl;

  // std::cout << list.size() << std::endl;

  // 1000 -> 10
  // list.erase(list.back());

  // std::cout << list.size() << std::endl;

  // for (const auto &node : list) {
  //   std::cout << node << " ";
  // }
}
