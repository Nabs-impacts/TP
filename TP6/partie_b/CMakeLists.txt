cmake_minimum_required(VERSION 3.28)
project(ModulesUIN LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(uin_regles)
target_sources(uin_regles
    PUBLIC
        FILE_SET CXX_MODULES FILES regles.cppm
    PRIVATE
        regles_impl.cpp)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE uin_regles)
