#include "sequential/empty_container.hpp"

namespace containers{

      const char* empty_container::what() const noexcept {
        return "This operation on empty container is not allowed";
      }    
}