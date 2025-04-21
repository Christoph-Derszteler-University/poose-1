cmake_minimum_required(VERSION 3.30)
project(poose_1)

set(CMAKE_CXX_STANDARD 26)

add_executable(
  poose_1
  main.cpp
  include/container.hpp
  include/associative/associative_container.hpp
)