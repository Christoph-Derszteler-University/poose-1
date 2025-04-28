if (WIN32)
  set(CMAKE_CXX_COMPILER "C:/Program Files/mingw/bin/clang++.exe" CACHE STRING "")
  set(CMAKE_C_COMPILER "C:/Program Files/mingw/bin/clang.exe" CACHE STRING "")
endif()

cmake_minimum_required(VERSION 3.30)
project(poose_1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Include Verzeichnis hinzufügen
include_directories(${PROJECT_SOURCE_DIR}/include)

# Alle .cpp-Dateien aus dem src/ Ordner
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Erstelle das Haupt-Executable
#add_executable(poose_1 ${SRC_FILES})

# Erstelle das Beispiel-Executable für den Stack
add_executable(stack_example examples/sequential/stack_example.cpp ${SRC_FILES})

# Weitere Beispiele
#add_executable(hash_map_example examples/associative/hash_map_example.cpp ${SRC_FILES})
#add_executable(hash_multi_map_example examples/associative/hash_multi_map_example.cpp ${SRC_FILES})
#add_executable(hash_set_example examples/associative/hash_set_example.cpp ${SRC_FILES})
#add_executable(hash_multi_set_example examples/associative/hash_multi_set_example.cpp ${SRC_FILES})
