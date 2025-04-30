#include <iostream>
#include <sequential/linked_list.hpp>

int main() {
  containers::sequential::linked_list<int> list;

  list.push_front(5);
  list.push_front(10);
  const auto head = list.front();
  list.erase_after(head);
  auto tail = list.insert_after(head, 40);

  std::cout << list.size() << std::endl;

  for (auto node = list.front(); node != nullptr; node = node->next) {
    std::cout << node->data << " ";
  }
}
