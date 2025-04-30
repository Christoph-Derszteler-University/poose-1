#include "sequential/empty_container.hpp"

namespace containers::sequential{

      const char* empty_container::what() const noexcept {
        return "Operation on empty container is not allowed";
      }    
}