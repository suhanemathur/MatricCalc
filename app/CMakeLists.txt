cmake_minimum_required(VERSION 3.4.1)

# Project name
project(MatrixCalc)

# Add native library
add_library(
        matrix_lib         # Name of your native lib
        SHARED             # Build a shared library
        src/main/cpp/matrix_lib.cpp  # Correct relative path to cpp file
)

# Include the JNI headers
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp)

# Link system libraries (like log)
find_library(log-lib log)

# Link with system log-lib
target_link_libraries(
        matrix_lib
        ${log-lib}
)
