#pragma once

#include <container.hpp>
#include <memory>

namespace containers::sequential {

/// @brief Abstract base class for a singly linked list.
///
/// This abstract class defines the core interface and internal structures
/// for a singly linked list, including basic operations such as insertion,
/// deletion, and traversal using smart pointers.
///
/// @tparam Type The type of elements stored in the list.
template <typename Type>
class abstract_linked_list : public container {
protected:
  /// @brief Internal node structure used in the linked list.
  struct node {
    /// @brief The data stored in the node.
    Type data;

    /// @brief Shared pointer to the next node in the list.
    std::shared_ptr<node> next;

    /// @brief Constructs a node with the specified value.
    /// @param value The value to store in the node.
    node(Type value);
  };

  /// @brief Type alias for a shared pointer to a Node.
  using node_t = std::shared_ptr<node>;

  /// @brief Virtual destructor for cleanup in derived classes.
  virtual ~abstract_linked_list() override = default;

  /// @brief Checks whether the list is empty.
  /// @return True if the list is empty, false otherwise.
  virtual bool empty() const noexcept = 0;

  /// @brief Removes all elements from the list.
  virtual void clear() noexcept = 0;

  /// @brief Returns a shared pointer to the first node in the list.
  /// @return A shared pointer to the front node, or nullptr if the list is empty.
  virtual node_t front() const noexcept = 0;

  /// @brief Inserts a new element at the beginning of the list.
  /// @param val The value to insert.
  virtual void push_front(Type val) = 0;

  /// @brief Removes the first element from the list.
  virtual void pop_front() = 0;

  /// @brief Removes the node immediately following the given position.
  ///
  /// If the provided position is nullptr or has no next node, the function
  /// returns nullptr.
  ///
  /// @param pos A shared pointer to the node before the one to remove.
  /// @return A shared pointer to the node that follows the removed node,
  /// or nullptr.
  virtual node_t erase_after(node_t pos) = 0;

  /// @brief Inserts a new element after the given position.
  ///
  /// If the position is nullptr, no insertion is performed.
  ///
  /// @param pos A shared pointer to the node after which the new value
  /// will be inserted.
  /// @param val The value to insert.
  /// @return A shared pointer to the newly inserted node, or nullptr if
  /// insertion fails.
  virtual node_t insert_after(node_t pos, Type val) = 0;
};

/// @brief A singly linked list container implementation.
///
/// Provides basic operations such as insertion, deletion, and traversal using
/// smart pointers.
///
/// @tparam Type The type of elements stored in the list.
template <typename Type>
class linked_list : public abstract_linked_list<Type> {
private:
  using node = abstract_linked_list<Type>::node;
  using node_t = abstract_linked_list<Type>::node_t;

  /// @brief Pointer to the first node in the list.
  node_t head;

public:
  /// @brief Constructs an empty linked list.
  linked_list();

  /// @brief Checks whether the list is empty.
  /// @return True if the list has no elements, false otherwise.
  bool empty() const noexcept override;

  /// @brief Removes all elements from the list.
  void clear() noexcept override;

  /// @brief Returns a shared pointer to the first node in the list.
  /// @return A shared pointer to the front node, or nullptr if the list is empty.
  node_t front() const noexcept override;

  /// @brief Inserts a new element at the beginning of the list.
  /// @param val The value to insert.
  void push_front(Type val) override;

  /// @brief Removes the first element from the list.
  void pop_front() override;

  /// @brief Removes the node immediately following the given position.
  ///
  /// If the provided position is nullptr or has no next node, the function
  /// returns nullptr.
  ///
  /// @param pos A shared pointer to the node before the one to remove.
  /// @return A shared pointer to the node that follows the removed node, or
  /// nullptr.
  node_t erase_after(node_t pos) override;

  /// @brief Inserts a new element after the given position.
  ///
  /// If the position is nullptr, no insertion is performed.
  ///
  /// @param pos A shared pointer to the node after which the new value will be
  /// inserted.
  /// @param val The value to insert.
  /// @return A shared pointer to the newly inserted node, or nullptr if
  /// insertion fails.
  node_t insert_after(node_t pos, Type val) override;
};

} // namespace containers::sequential

#include <sequential/inline/linked_list.tpp>

