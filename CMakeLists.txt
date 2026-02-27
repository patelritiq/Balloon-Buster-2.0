cmake_minimum_required(VERSION 3.10)

project(BalloonBuster VERSION 2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(balloon_buster
    src/balloon_buster.cpp
)

target_compile_features(balloon_buster PRIVATE cxx_std_17)

if(MSVC)
    target_compile_options(balloon_buster PRIVATE /W4)
else()
    target_compile_options(balloon_buster PRIVATE -Wall -Wextra -Wpedantic)
endif()