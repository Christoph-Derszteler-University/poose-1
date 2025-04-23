#include <memory>
#include <sequential/linked_list.hpp>

namespace containers::sequential {

template <typename Type> linked_list<Type>::linked_list() = default;

template <typename Type>
linked_list<Type>::Node::Node(Type value) : data(value){};

template <typename Type> const size_t linked_list<Type>::size() {
  return length;
}

template <typename Type> bool linked_list<Type>::empty() const noexcept {
  return size() == 0;
}

template <typename Type> void linked_list<Type>::clear() noexcept {
  head = nullptr;
  length = 0;
}

template <typename Type>
std::shared_ptr<typename linked_list<Type>::Node>
linked_list<Type>::front() const noexcept {
  return head;
}

template <typename Type> void linked_list<Type>::push_front(Type val) {
  auto new_node = std::make_shared<Node>(val);
  new_node->next = head;
  head = new_node;
  length++;
}

template <typename Type>
std::shared_ptr<typename linked_list<Type>::Node>
linked_list<Type>::erase_after(std::shared_ptr<Node> pos) {
  if (pos == nullptr || pos->next == nullptr) {
    return nullptr;
  }

  pos->next = pos->next->next;

  length--;

  return pos->next;
}

template <typename Type>
std::shared_ptr<typename linked_list<Type>::Node>
linked_list<Type>::insert_after(std::shared_ptr<Node> pos, Type val) {
  if (pos == nullptr)
    return nullptr;

  const auto after = std::make_shared<Node>(val);

  const std::shared_ptr<Node> temp = pos->next;

  pos->next = after;

  after->next = temp;

  length++;

  return after;
}

template <typename Type> void linked_list<Type>::pop_front() {
  if (head == nullptr)
    return;
  head = head->next;
  length--;
}
} // namespace containers::sequential