#include <sequential/doubly_linked_list.hpp>

namespace containers::sequential {

template <typename T> doubly_linked_list<T>::doubly_linked_list() = default;

template <typename T>
doubly_linked_list<T>::Node::Node(T value) : data(value){};

/* Capacity */

template <typename T> const size_t doubly_linked_list<T>::size() {
  return m_length;
}

template <typename T> bool doubly_linked_list<T>::empty() {
  return size() == 0;
}

/* Element Access */

template <typename T>
doubly_linked_list<T>::Node_t doubly_linked_list<T>::front() const noexcept {
  return m_head;
}

template <typename T>
doubly_linked_list<T>::Node_t doubly_linked_list<T>::back() const noexcept {
  return m_tail;
}

/* Modifiers */

template <typename T> void doubly_linked_list<T>::clear() noexcept {
  m_head = m_tail = nullptr;
  m_length = 0;
}

template <typename T>
doubly_linked_list<T>::Node_t doubly_linked_list<T>::insert(Node_t pos, T val) {
  if (pos == nullptr)
    return nullptr;

  const auto newNode = std::make_shared<Node>(val);

  if (pos == m_head) {
    newNode->next = m_head;
    m_head->prev = newNode;
    m_head = newNode;
  } else {
    newNode->next = pos;
    newNode->prev = pos->prev;
    pos->prev.lock()->next = newNode;
    pos->prev = newNode;
  }

  m_length++;

  return newNode;
}

template <typename T>
doubly_linked_list<T>::Node_t doubly_linked_list<T>::erase(Node_t pos) {
  if (pos == nullptr)
    return nullptr;

  m_length--;
  if (pos == m_head) {
    m_head = pos->next;
    pos->next = nullptr;
    return m_head;
  } else if (pos == m_tail) {
    m_tail = pos->prev.lock();
    pos->prev.lock()->next = nullptr;
    return m_tail;
  } else {
    const auto prev = pos->prev.lock();
    prev->next = pos->next;
    pos->next->prev = prev;
    return pos->next;
  }
}

template <typename T> void doubly_linked_list<T>::push_back(T val) {
  const auto newNode = std::make_shared<Node>(val);

  if (empty()) {
    m_head = m_tail = newNode;
  } else {
    m_tail->next = newNode;
    newNode->prev = m_tail;
    m_tail = newNode;
  }
  m_length++;
}

template <typename T> void doubly_linked_list<T>::pop_back() noexcept {
  if (empty())
    return;

  const auto prev = m_tail->prev.lock();
  if (prev != nullptr) {
    prev->next = nullptr;
  } else {
    m_head = nullptr;
  }
  m_tail = prev;

  m_length--;
}

template <typename T> void doubly_linked_list<T>::push_front(T val) {
  const auto newNode = std::make_shared<Node>(val);
  if (empty()) {
    m_head = m_tail = newNode;
  } else {
    newNode->next = m_head;
    m_head->prev = newNode;
    m_head = newNode;
  }

  m_length++;
}

template <typename T> void doubly_linked_list<T>::pop_front() noexcept {
  if (!empty()) {
    m_head = m_head->next;
    m_length--;
  }
}
} // namespace containers::sequential
