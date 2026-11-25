configure_file(config.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/uincampus/config.hpp
    @ONLY)

add_library(uincampus_core
    version.cpp
    regles.cpp
    saisie.cpp
    calculs.cpp)
add_library(uin::core ALIAS uincampus_core)

target_include_directories(uincampus_core
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)

target_compile_features(uincampus_core PUBLIC cxx_std_23)
target_link_libraries(uincampus_core PRIVATE uincampus_options)

option(UIN_PCH "Activer les en-têtes précompilés" OFF)
if(UIN_PCH)
    target_precompile_headers(uincampus_core PRIVATE
        <format> <print> <string> <string_view> <vector>)
endif()
