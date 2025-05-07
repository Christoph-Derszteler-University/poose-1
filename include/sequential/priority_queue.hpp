#pragma once

#include <container.hpp>
#include <memory>

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
   * @brief protected struct for nodes in the priority queue
   */
  struct heap_node {
    using shared_node_t = std::shared_ptr<heap_node>;
    using weak_node_t = std::weak_ptr<heap_node>;

    T data;               //< The data to be stored
    shared_node_t left;   //< Pointer to left child node
    shared_node_t right;  //< Pointer to right child node
    weak_node_t parent;   //< Pointer to parent node

    /**
     * @brief Construct a new heap_node with the given value.
     *
     * @param value The value to store in the node.
     */
    heap_node(const T& value);
  };
  using heap_node_t = std::shared_ptr<heap_node>;
protected:
  /**
   * @brief Protected virtual destructor to ensure proper cleanup through base class pointers.
   */
  virtual ~abstract_priority_queue() override = default;
  /**
   * @brief Access the top (highest priority) element.
   * 
   * @return Value of the top element.
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
private:
  using heap_node = typename abstract_priority_queue<T>::heap_node;
  using heap_node_t = typename abstract_priority_queue<T>::heap_node_t;

  heap_node_t root; ///< Pointer to the root of the priority queue.
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
   * @brief Maintains the heap property after insertion by bubbling the element up.
   * 
   * @param index The index of the newly inserted element.
   */
  void heapify_up(std::shared_ptr<typename abstract_priority_queue<T>::heap_node> node);

  /**
   * @brief Maintains the heap property after removal by bubbling the element down.
   * 
   * @param index The index from which to start the heapify down process.
   */
  void heapify_down(std::shared_ptr<typename abstract_priority_queue<T>::heap_node> node);
};

} // namespace containers::sequential

#include "inline/priority_queue.tpp"
