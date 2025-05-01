#include "sequential/empty_container.hpp"

namespace containers::sequential{

      const char* empty_container::what() const noexcept {
        return "This operation is not allowed on an empty container";
      }    
}