cmake_minimum_required(VERSION 3.4)

# we need LLVM_HOME in order not automatically set LLVM_DIR
SET(CMAKE_C_COMPILER /usr/lib/llvm-9/bin/clang-9)
SET(CMAKE_CXX_COMPILER /usr/lib/llvm-9/bin/clang++)
if(NOT DEFINED ENV{LLVM_HOME})
    message(FATAL_ERROR "$LLVM_HOME is not defined")
else ()
    set(ENV{LLVM_DIR} $ENV{LLVM_HOME}/lib/cmake/llvm)
endif()

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(PointerAnalysis) # Use your pass name here.
