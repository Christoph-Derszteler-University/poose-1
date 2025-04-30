#pragma once

#include <container.hpp>
#include <functional>
#include <vector>

namespace containers::sequential {

template <typename T, typename Compare = std::less<T>>
class abstract_priority_queue : public container {
protected:
  virtual ~abstract_priority_queue() override = default;

  virtual const T &top() const = 0;

  virtual void push(const T &value) = 0;
  virtual void pop() = 0;
};

template <typename T, typename Compare = std::less<T>>
class priority_queue : public abstract_priority_queue<T, Compare> {
public:
  priority_queue();

  [[nodiscard]] const T &top() const override;

  void push(const T &value) override;
  void pop() override;

private:
  std::vector<T> heap;
  Compare comp;

  void heapifyUp(std::size_t index);
  void heapifyDown(std::size_t index);
};
} // namespace containers::sequential

#include "inline/priority_queue.tpp"
