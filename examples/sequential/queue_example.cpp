#include "sequential/list_queue.hpp"
#include <iostream>
#include <string>

using namespace containers::sequential;

int main() {
    list_queue<int> my_int_queue;
    list_queue<std::string> my_str_queue;

    my_int_queue.enqueue(2);
    my_int_queue.enqueue(4);

    size_t amount = my_int_queue.size();
    std::cout << "queue has " << amount << " members." << std::endl;

    int first_element = my_int_queue.dequeue();
    std::cout << first_element << " was first in queue." << std::endl;

    amount = my_int_queue.size();
    std::cout << "queue has " << amount << " members." << std::endl;

    //TODO: Make example suitable for presentation
    my_str_queue.enqueue("alright mate! queues not empty");
    if (my_str_queue.isEmpty()) {
        std::cout << "queue ist empty" << std::endl;
    }
    std::string str = my_str_queue.dequeue();
    std::cout << str << std::endl;

}