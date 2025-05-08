# Configure CMake
if (WIN32)
  set(CMAKE_CXX_COMPILER "C:/Program Files/mingw/bin/clang++.exe" CACHE STRING "")
  set(CMAKE_C_COMPILER "C:/Program Files/mingw/bin/clang.exe" CACHE STRING "")
endif()

cmake_minimum_required(VERSION 3.30)
project(poose_1)

# Set compiler options

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Add project sources

include_directories(include)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Examples

add_executable(queue_example examples/sequential/queue_example.cpp ${SRC_FILES})
add_executable(stack_example examples/sequential/stack_example.cpp ${SRC_FILES})
add_executable(priority_queue_example examples/sequential/priority_queue.cpp ${SRC_FILES})
add_executable(linked_list_example examples/sequential/linked_list.cpp ${SRC_FILES})
add_executable(doubly_linked_list_example examples/sequential/doubly_linked_list.cpp ${SRC_FILES})

add_executable(hash_map_example examples/associative/hash_map_example.cpp ${SRC_FILES})
add_executable(hash_multi_map_example examples/associative/hash_multi_map_example.cpp ${SRC_FILES})
add_executable(hash_set_example examples/associative/hash_set_example.cpp ${SRC_FILES})
add_executable(hash_multi_set_example examples/associative/hash_multi_set_example.cpp ${SRC_FILES})

# Benchmarks

function(add_benchmark name source)
  add_executable(${name}_benchmark ${source} benchmarks/benchmark.cpp ${SRC_FILES})
  target_include_directories(${name}_benchmark PRIVATE benchmarks)
  if (WIN32)
    target_link_libraries(${name}_benchmark PRIVATE "-Wl,--stack,8589934592") # Increases stack size to 1GB
  endif()
endfunction()

add_benchmark(priority_queue benchmarks/sequential/priority_queue_benchmark.cpp)
add_benchmark(hash_map benchmarks/associative/hash_map/hash_map_benchmark.cpp)
add_benchmark(hash_multi_set benchmarks/associative/hash_multi_set/hash_multi_set_benchmark.cpp)

# Tests

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/cd430b47a54841ec45d64d2377d7cabaf0eba610.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
include(GoogleTest)

# Associative containers tests
add_executable(hash_set_test tests/associative/hash_set_test.cpp ${SRC_FILES})
target_link_libraries(hash_set_test GTest::gtest_main)
add_executable(hash_map_test tests/associative/hash_map_test.cpp ${SRC_FILES})
target_link_libraries(hash_map_test GTest::gtest_main)
add_executable(hash_multi_set_test tests/associative/hash_multi_set_test.cpp ${SRC_FILES})
target_link_libraries(hash_multi_set_test GTest::gtest_main)
add_executable(hash_multi_map_test tests/associative/hash_multi_map_test.cpp ${SRC_FILES})
target_link_libraries(hash_multi_map_test GTest::gtest_main)
gtest_discover_tests(hash_set_test hash_map_test hash_multi_set_test hash_multi_map_test)

# Sequential containers tests
add_executable(stack_test tests/sequential/stack_test.cpp ${SRC_FILES})
target_link_libraries(stack_test GTest::gtest_main)
add_executable(queue_test tests/sequential/queue_test.cpp ${SRC_FILES})
target_link_libraries(queue_test GTest::gtest_main)
gtest_discover_tests(queue_test)
add_executable(linked_list_test tests/sequential/linked_list_test.cpp ${SRC_FILES})
target_link_libraries(linked_list_test GTest::gtest_main)
add_executable(doubly_linked_list_test tests/sequential/doubly_linked_list_test.cpp ${SRC_FILES})
target_link_libraries(doubly_linked_list_test GTest::gtest_main)
gtest_discover_tests(linked_list_test doubly_linked_list_test)
