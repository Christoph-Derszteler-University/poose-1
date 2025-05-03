namespace containers::sequential {

template <typename T> priority_queue<T>::priority_queue() = default;

template <typename T> void priority_queue<T>::push(const T &value) {
  heap.push_back(value);
  container::number_elements++;
  heapifyUp(container::number_elements - 1);
}

template <typename T> void priority_queue<T>::pop() {
  if (container::empty()) {
    throw std::out_of_range("PriorityQueue is empty.");
  }

  std::swap(heap.front()->data, heap.back()->data);
  heap.pop_back();
  container::number_elements--;
  if (!heap.empty()) {
    heapifyDown(0);
  }
}

template <typename T> const T &priority_queue<T>::top() const {
  if (heap.empty()) {
    throw std::out_of_range("PriorityQueue is empty.");
  }
  return heap.front()->data;
}

template <typename T> void priority_queue<T>::heapifyUp(std::size_t index) {
  while (index > 0) {
    size_t parent = (index - 1) / 2;
    // if heap[parent] < heap[index], swap for max-heap
    if (heap.at(parent)->data < heap.at(index)->data) {
      std::swap(heap.at(parent)->data, heap.at(index)->data);
      index = parent;
    } else {
      break;
    }
  }
}

template <typename T> void priority_queue<T>::heapifyDown(std::size_t index) {
  size_t n = container::number_elements;
  while (true) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t largest = index;

    if (left < n && heap.at(largest)->data < heap.at(left)->data) {
      largest = left;
    }
    if (right < n && heap.at(largest)->data < heap.at(right)->data) {
      largest = right;
    }
    if (largest != index) {
      std::swap(heap.at(index)->data, heap.at(largest)->data);
      index = largest;
    } else {
      break;
    }
  }
}
} // namespace containers::sequential
