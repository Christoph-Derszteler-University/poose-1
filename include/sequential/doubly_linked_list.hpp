#pragma once

#include <container.hpp>
#include <memory>

namespace containers::sequential {

/**
 * @brief Abstract base class for a doubly linked list container.
 *
 * Defines the interface for a generic doubly linked list.
 *
 * @tparam T The type of the elements stored in the list.
 */
template <typename T> class abstract_doubly_linked_list : public container {
protected:
  /**
   * @brief Internal node structure for the doubly linked list.
   */
  struct node {
    T data;                     ///< The data stored in the node.
    std::shared_ptr<node> next; ///< Pointer to the next node.
    std::weak_ptr<node> prev;   ///< Weak pointer to the previous node.

    /**
     * @brief Construct a new Node with the given value.
     *
     * @param value The value to store in the node.
     */
    node(T value);
  };

  using node_t = std::shared_ptr<node>;

  /**
   * @brief Virtual destructor to ensure proper cleanup in derived classes.
   */
  virtual ~abstract_doubly_linked_list() override = default;

  /**
   * @brief Returns the front node of the list.
   *
   * @return A shared pointer to the front node.
   */
  virtual node_t front() const noexcept = 0;

  /**
   * @brief Returns the back node of the list.
   *
   * @return A shared pointer to the back node.
   */
  virtual node_t back() const noexcept = 0;

  /**
   * @brief Removes all elements from the list.
   */
  virtual void clear() noexcept = 0;

  /**
   * @brief Inserts a new element before the given node position.
   *
   * @param pos The position before which to insert the new node.
   * @param val The value to be inserted.
   * @return A shared pointer to the newly inserted node.
   */
  virtual node_t insert(node_t pos, T val) = 0;

  /**
   * @brief Removes the node at the specified position.
   *
   * @param pos The node to remove.
   * @return A shared pointer to the next node after the removed node.
   */
  virtual node_t erase(node_t pos) = 0;

  /**
   * @brief Appends an element to the back of the list.
   *
   * @param val The value to be appended.
   */
  virtual void push_back(T val) = 0;

  /**
   * @brief Removes the last element of the list.
   */
  virtual void pop_back() noexcept = 0;

  /**
   * @brief Inserts an element at the front of the list.
   *
   * @param val The value to be inserted.
   */
  virtual void push_front(T val) = 0;

  /**
   * @brief Removes the first element of the list.
   */
  virtual void pop_front() noexcept = 0;
};

/**
 * @brief A generic doubly linked list implementation.
 *
 * Provides standard operations for adding, removing, and accessing elements
 * in a doubly linked structure.
 *
 * @tparam T The type of the elements stored in the list.
 */
template <typename T>
class doubly_linked_list : public abstract_doubly_linked_list<T> {
private:
  using node = typename abstract_doubly_linked_list<T>::node;
  using node_t = typename abstract_doubly_linked_list<T>::node_t;

  node_t head_pointer; ///< Pointer to the head of the list.
  node_t tail_pointer; ///< Pointer to the tail of the list.

public:
  /**
   * @brief Construct a new, empty doubly linked list.
   */
  doubly_linked_list();

  /// @copydoc abstract_doubly_linked_list::front
  node_t front() const noexcept override;

  /// @copydoc abstract_doubly_linked_list::back
  node_t back() const noexcept override;

  /// @copydoc abstract_doubly_linked_list::clear
  void clear() noexcept override;

  /// @copydoc abstract_doubly_linked_list::insert
  node_t insert(node_t pos, T val) override;

  /// @copydoc abstract_doubly_linked_list::erase
  node_t erase(node_t pos) override;

  /// @copydoc abstract_doubly_linked_list::push_back
  void push_back(T val) override;

  /// @copydoc abstract_doubly_linked_list::pop_back
  void pop_back() noexcept override;

  /// @copydoc abstract_doubly_linked_list::push_front
  void push_front(T val) override;

  /// @copydoc abstract_doubly_linked_list::pop_front
  void pop_front() noexcept override;
};

} // namespace containers::sequential

#include <sequential/inline/doubly_linked_list.tpp>
