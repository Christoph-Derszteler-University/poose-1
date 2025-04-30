# Configure CMake

if (WIN32)
  set(CMAKE_CXX_COMPILER "C:/Program Files/mingw/bin/clang++.exe" CACHE STRING "")
  set(CMAKE_C_COMPILER "C:/Program Files/mingw/bin/clang.exe" CACHE STRING "")
@@ -22,7 +21,10 @@ add_link_options(-fsanitize=address)
include_directories(include)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(poose_1 ${SRC_FILES})
# Sequential examples
add_executable(queue_example examples/sequential/queue_example.cpp ${SRC_FILES})
add_executable(stack_example examples/sequential/stack_example.cpp ${SRC_FILES})

# Associative examples
add_executable(hash_map_example examples/associative/hash_map_example.cpp ${SRC_FILES})
add_executable(hash_multi_map_example examples/associative/hash_multi_map_example.cpp ${SRC_FILES})
add_executable(hash_set_example examples/associative/hash_set_example.cpp ${SRC_FILES})
@@ -43,6 +45,7 @@ FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)


# Associative containers tests
add_executable(hash_set_test tests/associative/hash_set_test.cpp ${SRC_FILES})
target_link_libraries(hash_set_test GTest::gtest_main)
@@ -52,4 +55,4 @@ add_executable(hash_multi_set_test tests/associative/hash_multi_set_test.cpp ${S
target_link_libraries(hash_multi_set_test GTest::gtest_main)
add_executable(hash_multi_map_test tests/associative/hash_multi_map_test.cpp ${SRC_FILES})
target_link_libraries(hash_multi_map_test GTest::gtest_main)
gtest_discover_tests(hash_set_test hash_map_test hash_multi_set_test hash_multi_map_test)
\ No newline at end of file
gtest_discover_tests(hash_set_test hash_map_test hash_multi_set_test hash_multi_map_test)