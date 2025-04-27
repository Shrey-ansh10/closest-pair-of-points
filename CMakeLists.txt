cmake_minimum_required(VERSION 3.10)
project(ClosestPairOfPoints)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Add all source files
add_executable(ClosestPairOfPoints 
    main.cpp
    ClosestPair.cpp
)

# Enable all warnings and make them errors
if (MSVC)
    target_compile_options(ClosestPairOfPoints PRIVATE /W4)
else()
    target_compile_options(ClosestPairOfPoints PRIVATE -Wall -Wextra)
endif() 