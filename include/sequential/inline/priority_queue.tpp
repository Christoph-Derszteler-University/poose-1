#include "sequential/priority_queue.hpp"
#include "sequential/list_queue.hpp"

namespace containers::sequential {

template <typename T> priority_queue<T>::priority_queue() = default;

template <typename T>
void priority_queue<T>::push(const T &value) {
    using heap_node = typename abstract_priority_queue<T>::heap_node;
    // 1) new_node als shared_ptr anlegen
    auto new_node = std::make_shared<heap_node>(value);
    container::number_elements++;

    // 2) Wenn leerer Baum, new_node zur Wurzel machen und zurück
    if (!root) {
        root = new_node;
        return;
    }

    // 3) Level-Order-Breitensuche, um ersten freien Platz zu finden
    containers::sequential::list_queue<std::shared_ptr<heap_node>> queue;
    queue.enqueue(root);

    while (!queue.empty()) {
        auto current = queue.front();
        queue.dequeue(); 

        if (!current->left) {
            current->left = new_node;
            new_node->parent = current;
            break;
        } else {
            queue.enqueue(current->left);
        }

        if (!current->right) {
            current->right = new_node;
            new_node->parent = current;
            break;
        } else {
            queue.enqueue(current->right);
        }
    }

    // 4) Heapify-Up auf den gerade eingefügten Knoten
    heapify_up(new_node);
}


template <typename T>
void priority_queue<T>::pop() {
  if (!root) {
    throw std::out_of_range("PriorityQueue is empty.");
  }

  using node_ptr = typename abstract_priority_queue<T>::heap_node_t;

  if (container::number_elements == 1) {
    root.reset();  // nur ein Element
    container::number_elements--;
    return;
  }

  // Level-order-Suche nach dem letzten Knoten
  list_queue<node_ptr> queue;
  queue.enqueue(root);

  node_ptr last;
  node_ptr parent_of_last;

  while (!queue.empty()) {
    auto current = queue.front();
    queue.dequeue();
    last = current;

    if (current->left) {
      parent_of_last = current;
      queue.enqueue(current->left);
    }
    if (current->right) {
      parent_of_last = current;
      queue.enqueue(current->right);
    }
  }

  // Tausche root und last
  std::swap(root->data, last->data);

  // Entferne den letzten Knoten
  if (parent_of_last->right == last) {
    parent_of_last->right.reset();
  } else if (parent_of_last->left == last) {
    parent_of_last->left.reset();
  }

  container::number_elements--;

  // Heapify down
  heapify_down(root);
}


template <typename T> const T &priority_queue<T>::top() const {
  if (!root) {
    throw std::out_of_range("PriorityQueue is empty.");
  }
  return root->data;
}

template <typename T>
void priority_queue<T>::heapify_up(std::shared_ptr<typename abstract_priority_queue<T>::heap_node> node) {
  while (auto parent = node->parent.lock()) {
    if (parent->data < node->data) {
      std::swap(parent->data, node->data);
      node = parent;
    } else {
      break;
    }
  }
}


template <typename T>
void priority_queue<T>::heapify_down(std::shared_ptr<typename abstract_priority_queue<T>::heap_node> node) {
  while (node) {
    auto largest = node;
    
    if (node->left && node->left->data > largest->data) {
      largest = node->left;
    }
    if (node->right && node->right->data > largest->data) {
      largest = node->right;
    }

    if (largest != node) {
      std::swap(node->data, largest->data);
      node = largest;
    } else {
      break;
    }
  }
}
template<typename T>
inline containers::sequential::abstract_priority_queue<T>::heap_node::heap_node(const T& value) : data(value){}

} // namespace containers::sequential
