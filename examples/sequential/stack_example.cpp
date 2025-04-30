#include "sequential/list_stack.hpp"
#include <iostream>

using namespace containers::sequential;
    
int main() {
    list_stack<int> my_int_stack;
    my_int_stack.push(42);
    my_int_stack.push(71);
    my_int_stack.push(9);

    size_t list_size = my_int_stack.size();
    std::cout << "Die Größe hinter dem ':' sollte drei sein: " << list_size << std::endl;

    int vorne = my_int_stack.pop();
    std::cout << "Das oberste Element auf dem Stack war " << vorne << std::endl;

    if (my_int_stack.empty()) {
        std::cout << "Der Stack ist leer" << std::endl;
    } else {
        std::cout << "Der Stack ist noch nicht leer" << std::endl;
    }
}
