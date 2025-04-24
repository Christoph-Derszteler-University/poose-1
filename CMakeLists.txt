if (WIN32)
  set(CMAKE_CXX_COMPILER "C:/Program Files/mingw/bin/clang++.exe" CACHE STRING "")
  set(CMAKE_C_COMPILER "C:/Program Files/mingw/bin/clang.exe" CACHE STRING "")
endif()

set(CMAKE_CXX_STANDARD 26)

cmake_minimum_required(VERSION 3.30)
project(poose_1)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

include_directories(include)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(poose_1 ${SRC_FILES})
add_executable(hash_map_example examples/associative/hash_map_example.cpp ${SRC_FILES})
add_executable(hash_multi_map_example examples/associative/hash_multi_map_example.cpp ${SRC_FILES})
 add_executable(hash_set_example examples/associative/hash_set_example.cpp ${SRC_FILES})
add_executable(hash_multi_set_example examples/associative/hash_multi_set_example.cpp ${SRC_FILES})