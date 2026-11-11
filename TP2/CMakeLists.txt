cmake_minimum_required(VERSION 3.25)
project(UINCampus
    VERSION 0.1.0
    DESCRIPTION "Système de gestion académique de l'UIN"
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(UIN_ACTIVER_SANITIZERS "Activer Address Sanitizer et UBSan" OFF)

add_library(uincampus_options INTERFACE)
target_compile_features(uincampus_options INTERFACE cxx_std_23)

if(MSVC)
    target_compile_options(uincampus_options INTERFACE /W4 /permissive-)
else()
    target_compile_options(uincampus_options INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

if(UIN_ACTIVER_SANITIZERS AND NOT MSVC)
    target_compile_options(uincampus_options INTERFACE
        -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(uincampus_options INTERFACE
        -fsanitize=address,undefined)
endif()

add_library(uincampus_core src/version.cpp)
target_include_directories(uincampus_core PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(uincampus_core PRIVATE UIN_VERSION="${PROJECT_VERSION}")
target_link_libraries(uincampus_core PRIVATE uincampus_options)

add_executable(uin-campus app/main.cpp)
target_link_libraries(uin-campus PRIVATE uincampus_core uincampus_options)
