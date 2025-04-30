#include "include/sequential/empty_container.hpp"

namespace containers::sequential{
class empty_container : public std::exception {
    public:
      const char* what() const noexcept override {
        return "Operation on empty container is not allowed";
      }
    };    
}