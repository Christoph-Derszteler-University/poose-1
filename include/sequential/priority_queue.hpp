#pragma once

#include <container.hpp>
#include <sequential/doubly_linked_list.hpp>

namespace containers::sequential {

/**
 * @brief Abstract base class for a priority queue.
 * 
 * This class defines the interface for a priority queue data structure, 
 * supporting access to the top element, insertion, and removal of elements.
 * 
 * @tparam T The type of elements stored in the priority queue.
 */
template <typename T> 
class abstract_priority_queue : public container {
protected:
  /**
   * @brief Protected virtual destructor to ensure proper cleanup through base class pointers.
   */
  virtual ~abstract_priority_queue() override = default;

  /**
   * @brief Access the top (highest priority) element.
   * 
   * @return Reference to the top element.
   * @throws std::out_of_range if the priority queue is empty.
   */
  [[nodiscard]] virtual const T &top() const = 0;

  /**
   * @brief Insert an element into the priority queue.
   * 
   * @param value The value to insert.
   */
  virtual void push(const T &value) = 0;

  /**
   * @brief Remove the top (highest priority) element from the queue.
   * 
   * @throws std::out_of_range if the priority queue is empty.
   */
  virtual void pop() = 0;
};

/**
 * @brief A max-heap based priority queue implementation using a doubly linked list.
 * 
 * Elements are maintained in a binary heap order, where the highest priority element 
 * is always accessible at the top.
 * 
 * @tparam T The type of elements stored in the priority queue.
 */
template <typename T> 
class priority_queue : public abstract_priority_queue<T> {
public:
  /**
   * @brief Constructs an empty priority queue.
   */
  priority_queue();

  // @copydoc abstract_priority_queue::top
  [[nodiscard]] const T &top() const override;

  // @copydoc abstract_priority_queue::push
  void push(const T &value) override;

  //@copydoc abstract_priority_queue::pop
  void pop() override;

private:
  /**
   * @brief Internal storage for the heap using a doubly linked list.
   */
  doubly_linked_list<T> heap;

  /**
   * @brief Maintains the heap property after insertion by bubbling the element up.
   * 
   * @param index The index of the newly inserted element.
   */
  void heapifyUp(std::size_t index);

  /**
   * @brief Maintains the heap property after removal by bubbling the element down.
   * 
   * @param index The index from which to start the heapify down process.
   */
  void heapifyDown(std::size_t index);
};

} // namespace containers::sequential

#include "inline/priority_queue.tpp"
