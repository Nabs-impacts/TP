cmake_minimum_required(VERSION 3.20)
project(tp3_statistiques_notes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tp3 src/main.cpp)

if(MSVC)
  target_compile_options(tp3 PRIVATE /W4 /utf-8)
else()
  target_compile_options(tp3 PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
