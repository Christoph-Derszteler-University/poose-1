#include <iostream>
#include <sequential/priority_queue.hpp>

int main() {
  containers::sequential::priority_queue<int> pqueue;

  pqueue.push(5);
  pqueue.push(10);
  pqueue.push(-40);

  std::cout << pqueue.top() << std::endl;

  pqueue.pop();

  std::cout << pqueue.top() << std::endl;
}
