#include <iostream>
#include <sequential/priority_queue.hpp>

int main() {
  containers::sequential::priority_queue<int> pqueue;

  pqueue.push(5);

  std::cout << pqueue.top() << std::endl;
}
