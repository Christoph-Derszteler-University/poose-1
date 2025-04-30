namespace containers::sequential {
template <typename T, typename Compare>
priority_queue<T, Compare>::priority_queue() {}

template <typename T, typename Compare>
void priority_queue<T, Compare>::push(const T& value) {
    heap.push_back(value);
    container::number_elements++;
    heapifyUp(container::number_elements - 1);
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::pop() {
    if (container::empty()) {
      return;
    }

    std::swap(heap.front(), heap.back());
    heap.pop_back();
    container::number_elements++;
    heapifyDown(0);
}

template <typename T, typename Compare>
const T& priority_queue<T, Compare>::top() const {
    return heap.front();
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::heapifyUp(std::size_t index) {
    while (index > 0) {
        std::size_t parent = (index - 1) / 2;
        if (!comp(heap[index], heap[parent])) {
          break;
        }

        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

template <typename T, typename Compare>
void priority_queue<T, Compare>::heapifyDown(std::size_t index) {
    std::size_t size = container::number_elements;
    while (index * 2 + 1 < size) {
      std::size_t left = index * 2 + 1;
      std::size_t right = index * 2 + 2;
      std::size_t smallest = left;

      if (right < size && comp(heap[right], heap[left])) {
        smallest = right;
      }

      if (!comp(heap[smallest], heap[index])) {
        break;
      }

      std::swap(heap[index], heap[smallest]);
      index = smallest;
    }
}
}
