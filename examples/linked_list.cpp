#include "../src/sequential/linked_list.cpp"
#include <iostream>

int main() {
  containers::sequential::linked_list<int> l;

  l.push_front(5);
  l.push_front(10);
  const auto head = l.front();
  l.erase_after(head);
  auto tail = l.insert_after(head, 40);

  std::cout << tail->data << std::endl;
  return 0;
}
