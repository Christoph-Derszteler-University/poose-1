#include <sequential/linked_list.hpp>
#include <iostream>

int main() {
  containers::sequential::linked_list<int> l;

  l.push_front(5);
  l.push_front(10);
  const auto head = l.front();
  l.erase_after(head);
  auto tail = l.insert_after(head, 40);

  for (auto node = l.front(); node != nullptr; node = node->next) {
    std::cout << node->data << " ";
  }
}
