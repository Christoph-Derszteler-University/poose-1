#include "sequential/empty_container.hpp"

namespace containers::sequential{

      const char* empty_container::what() const noexcept {
        return "This operation on  an empty container is not allowed";
      }    
}