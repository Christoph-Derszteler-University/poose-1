#include <sequential/doubly_linked_list.hpp>

namespace containers::sequential {

template <typename T> doubly_linked_list<T>::doubly_linked_list() = default;

template <typename T>
abstract_doubly_linked_list<T>::node::node(T value) : data(value){};

template <typename T>
doubly_linked_list<T>::node_t doubly_linked_list<T>::front() const noexcept {
  return head_pointer;
}

template <typename T>
doubly_linked_list<T>::node_t doubly_linked_list<T>::back() const noexcept {
  return tail_pointer;
}

template <typename T> void doubly_linked_list<T>::clear() noexcept {
  head_pointer = tail_pointer = nullptr;
  container::number_elements = 0;
}

template <typename T>
doubly_linked_list<T>::node_t doubly_linked_list<T>::insert(node_t pos, T val) {
  if (pos == nullptr) {
    return nullptr;
  }

  const auto new_node = std::make_shared<node>(val);

  if (pos == head_pointer) {
    new_node->next = head_pointer;
    head_pointer->prev = new_node;
    head_pointer = new_node;
  } else {
    new_node->next = pos;
    new_node->prev = pos->prev;
    pos->prev.lock()->next = new_node;
    pos->prev = new_node;
  }

  container::number_elements++;
  return new_node;
}

template <typename T>
doubly_linked_list<T>::node_t doubly_linked_list<T>::erase(node_t pos) {
  if (pos == nullptr) {
    return nullptr;
  }

  container::number_elements--;
  if (pos == head_pointer) {
    head_pointer = pos->next;
    pos->next = nullptr;
    return head_pointer;
  } else if (pos == tail_pointer) {
    tail_pointer = pos->prev.lock();
    pos->prev.lock()->next = nullptr;
    return tail_pointer;
  } else {
    const auto prev = pos->prev.lock();
    prev->next = pos->next;
    pos->next->prev = prev;
    return pos->next;
  }
}

template <typename T> void doubly_linked_list<T>::push_back(T val) {
  const auto new_node = std::make_shared<node>(val);

  if (container::empty()) {
    head_pointer = tail_pointer = new_node;
  } else {
    tail_pointer->next = new_node;
    new_node->prev = tail_pointer;
    tail_pointer = new_node;
  }
  container::number_elements++;
}

template <typename T> void doubly_linked_list<T>::pop_back() noexcept {
  if (container::empty()) {
    return;
  }

  const auto prev = tail_pointer->prev.lock();
  if (prev != nullptr) {
    prev->next = nullptr;
  } else {
    head_pointer = nullptr;
  }
  tail_pointer = prev;

  container::number_elements--;
}

template <typename T> void doubly_linked_list<T>::push_front(T val) {
  const auto new_node = std::make_shared<node>(val);
  if (container::empty()) {
    head_pointer = tail_pointer = new_node;
  } else {
    new_node->next = head_pointer;
    head_pointer->prev = new_node;
    head_pointer = new_node;
  }

  container::number_elements++;
}

template <typename T> void doubly_linked_list<T>::pop_front() noexcept {
  if (!container::empty()) {
    head_pointer = head_pointer->next;
    container::number_elements--;
  }
}

template<typename T> T& doubly_linked_list<T>::at(size_t idx) const {
  if (idx >= container::number_elements) {
    throw std::out_of_range(std::format("The index '{}' is higher than the max allowed index '{}'", idx, container::number_elements - 1));
  }

  auto it = iterator();
  if (idx < static_cast<size_t>(container::number_elements / 2)) {
    it = iterator(head_pointer);
    for (size_t current_idx = 0; current_idx < idx; current_idx++) {
      it++;
    }
  } else {
    it = iterator(tail_pointer);
    for (size_t current_idx = container::number_elements - idx - 1; current_idx > 0; current_idx--) {
      it--;
    }
  }

  return *it;
}

template <typename T>
doubly_linked_list<T>::iterator doubly_linked_list<T>::begin() const {
  return iterator(head_pointer);
}

template <typename T>
doubly_linked_list<T>::iterator doubly_linked_list<T>::end() const {
  return iterator();
}

template <typename T> doubly_linked_list<T>::iterator::iterator() = default;

template <typename T>
doubly_linked_list<T>::iterator::iterator(node_t ptr) : current(ptr) {}

template <typename T> T &doubly_linked_list<T>::iterator::operator*() const {
  return current->data;
}

template <typename T> T *doubly_linked_list<T>::iterator::operator->() const {
  return &current->data;
}

template <typename T>
typename doubly_linked_list<T>::iterator &
doubly_linked_list<T>::iterator::operator++() {
  if (current != nullptr) {
    current = current->next;
  }
  return *this;
}

template <typename T>
typename doubly_linked_list<T>::iterator
doubly_linked_list<T>::iterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename T>
doubly_linked_list<T>::iterator &doubly_linked_list<T>::iterator::operator--() {
  if (current != nullptr) {
    current = current->prev.lock();
  }
  return *this;
}

template <typename T>
doubly_linked_list<T>::iterator
doubly_linked_list<T>::iterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename T>
bool doubly_linked_list<T>::iterator::operator==(const iterator &other) const {
  return current == other.current;
}

template <typename T>
bool doubly_linked_list<T>::iterator::operator!=(const iterator &other) const {
  return !(*this == other);
}
} // namespace containers::sequential
