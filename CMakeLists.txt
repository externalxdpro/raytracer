cmake_minimum_required ( VERSION 3.1.0...3.27.0 )

project ( raytracer LANGUAGES CXX )

# Set to C++20
set ( CMAKE_CXX_STANDARD          20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS        OFF )

# Source

set ( SOURCE
  src/main.cpp
)

include_directories(src)

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

# Compiler flags for GCC
add_compile_options(-Wnon-virtual-dtor)     # Class has virtual functions, but its destructor is not virtual
add_compile_options(-Wreorder)              # Data member will be initialized after [other] data member
add_compile_options(-Wmaybe-uninitialized)  # Variable improperly initialized
add_compile_options(-Wunused-variable)      # Variable is defined but unused

# Executables
add_executable(raytracer ${SOURCE})
