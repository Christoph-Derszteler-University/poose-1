#include <memory>

namespace containers::sequential {

template <typename Type> linked_list<Type>::linked_list() = default;

template <typename Type>
abstract_linked_list<Type>::Node::Node(Type value) : data(value){};

template <typename Type> bool linked_list<Type>::empty() const noexcept {
  return container::number_elements == 0;
}

template <typename Type> void linked_list<Type>::clear() noexcept {
  head = nullptr;
  container::number_elements = 0;
}

template <typename Type>
linked_list<Type>::Node_t linked_list<Type>::front() const noexcept {
  return head;
}

template <typename Type> void linked_list<Type>::push_front(Type val) {
  auto new_node = std::make_shared<Node>(val);
  new_node->next = head;
  head = new_node;
  container::number_elements++;
}

template <typename Type>
linked_list<Type>::Node_t linked_list<Type>::erase_after(Node_t pos) {
  if (pos == nullptr || pos->next == nullptr) {
    return nullptr;
  }

  pos->next = pos->next->next;

  container::number_elements--;

  return pos->next;
}

template <typename Type>
linked_list<Type>::Node_t linked_list<Type>::insert_after(Node_t pos,
                                                          Type val) {
  if (pos == nullptr)
    return nullptr;

  const auto after = std::make_shared<Node>(val);

  const Node_t temp = pos->next;

  pos->next = after;

  after->next = temp;

  container::number_elements++;

  return after;
}

template <typename Type> void linked_list<Type>::pop_front() {
  if (head == nullptr)
    return;
  head = head->next;
  container::number_elements--;
}
} // namespace containers::sequential
