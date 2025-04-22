cmake_minimum_required(VERSION 3.30)
project(poose_1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Memory Leaks prüfen
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Includes hinzufügen
include_directories(include)

# Programm(e) bauen
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/**/*.cpp)
add_executable(poose_1 examples/main.cpp ${SRC_FILES})
