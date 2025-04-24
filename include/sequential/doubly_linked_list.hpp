#pragma once

#include <container.hpp>
#include <memory>

namespace containers::sequential {

/**
 * @brief A generic doubly linked list implementation.
 *
 * Provides standard operations for adding, removing, and accessing elements
 * in a doubly linked structure.
 *
 * @tparam T The type of the elements stored in the list.
 */
template <typename T> class doubly_linked_list : public container {
private:
  /**
   * @brief Internal node structure for the doubly linked list.
   */
  struct Node {
    T data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

    /**
     * @brief Construct a new Node with the given value.
     *
     * @param value The value to store in the node.
     */
    Node(T value);
  };

  using Node_t = std::shared_ptr<Node>;

  Node_t m_head;
  Node_t m_tail;
  size_t m_length;

public:
  /**
   * @brief Construct a new, empty doubly linked list.
   */
  doubly_linked_list();

  /* Capacity */

  /**
   * @brief Returns the number of elements in the list.
   *
   * @return The number of elements.
   */
  const size_t size();

  /**
   * @brief Checks whether the list is empty.
   *
   * @return true if the list is empty, false otherwise.
   */
  bool empty();

  /* Element Access */

  /**
   * @brief Returns a pointer to the first node.
   *
   * @return A shared pointer to the head node.
   */
  Node_t front() const noexcept;

  /**
   * @brief Returns a pointer to the last node.
   *
   * @return A shared pointer to the tail node.
   */
  Node_t back() const noexcept;

  /* Modifiers */

  /**
   * @brief Removes all elements from the list.
   */
  void clear() noexcept;

  /**
   * @brief Inserts a new node with the specified value before the given
   * position.
   *
   * @param pos The position before which to insert.
   * @param val The value to insert.
   * @return A shared pointer to the newly inserted node, or nullptr if the
   * position is invalid.
   */
  Node_t insert(Node_t pos, T val);

  /**
   * @brief Removes the node at the given position.
   *
   * @param pos The node to remove.
   * @return A shared pointer to the next node after the removed one, or nullptr
   * if the position is invalid.
   */
  Node_t erase(Node_t pos);

  /**
   * @brief Adds an element to the end of the list.
   *
   * @param val The value to add.
   */
  void push_back(T val);

  /**
   * @brief Removes the last element of the list.
   */
  void pop_back() noexcept;

  /**
   * @brief Adds an element to the front of the list.
   *
   * @param val The value to add.
   */
  void push_front(T val);

  /**
   * @brief Removes the first element of the list.
   */
  void pop_front() noexcept;
};
} // namespace containers::sequential

#include <sequential/inline/doubly_linked_list.tpp>
