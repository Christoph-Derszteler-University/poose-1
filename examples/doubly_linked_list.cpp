#include <iostream>
#include <sequential/doubly_linked_list.hpp>

int main() {
  containers::sequential::doubly_linked_list<int> l;

  // 10 -> 5 -> 200
  l.push_front(5);
  l.push_front(10);
  l.push_back(200);

  // 10 -> 5
  l.pop_back();

  auto ten = l.front();
  // 1000 -> 10 -> 5
  l.insert(ten, 1000);

  // 1000 -> 10
  l.erase(l.back());

  for (auto head = l.front(); head != nullptr; head = head->next) {
    std::cout << head->data << " ";
  }
}
