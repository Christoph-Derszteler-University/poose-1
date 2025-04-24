#pragma once

#include <container.hpp>
#include <memory>

namespace containers::sequential {

/// @brief A singly linked list container implementation.
///
/// Provides basic operations such as insertion, deletion, and traversal using
/// smart pointers.
/// @tparam Type The type of elements stored in the list.
template <typename Type> class linked_list : public container {
private:
  /// @brief Internal node structure used in the linked list.
  struct Node {
    /// @brief The data stored in the node.
    Type data;

    /// @brief Shared pointer to the next node in the list.
    std::shared_ptr<Node> next;

    /// @brief Constructs a node with the specified value.
    /// @param value The value to store in the node.
    Node(Type value);
  };

  /// @brief The number of elements in the list.
  size_t length = 0;

  /// @brief Pointer to the first node in the list.
  std::shared_ptr<Node> head;

public:
  /// @brief Constructs an empty linked list.
  linked_list();

  /// @brief Returns the number of elements in the list.
  /// @return The number of elements currently stored.
  const size_t size();

  /// @brief Checks whether the list is empty.
  /// @return True if the list has no elements, false otherwise.
  bool empty() const noexcept;

  /// @brief Removes all elements from the list.
  void clear() noexcept;

  /// @brief Returns a shared pointer to the first node in the list.
  /// @return A shared pointer to the front node, or nullptr if the list is
  /// empty.
  std::shared_ptr<Node> front() const noexcept;

  /// @brief Inserts a new element at the beginning of the list.
  /// @param val The value to insert.
  void push_front(Type val);

  /// @brief Removes the first element from the list.
  void pop_front();

  /// @brief Removes the node immediately following the given position.
  ///
  /// If the provided position is nullptr or has no next node, the function
  /// returns nullptr.
  /// @param pos A shared pointer to the node before the one to remove.
  /// @return A shared pointer to the node that follows the removed node, or
  /// nullptr.
  std::shared_ptr<Node> erase_after(std::shared_ptr<Node> pos);

  /// @brief Inserts a new element after the given position.
  ///
  /// If the position is nullptr, no insertion is performed.
  /// @param pos A shared pointer to the node after which the new value will be
  /// inserted.
  /// @param val The value to insert.
  /// @return A shared pointer to the newly inserted node, or nullptr if
  /// insertion fails.
  std::shared_ptr<Node> insert_after(std::shared_ptr<Node> pos, Type val);
};

} // namespace containers::sequential

#include <sequential/inline/linked_list.tpp>
