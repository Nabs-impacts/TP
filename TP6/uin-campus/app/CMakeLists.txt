add_executable(uin-campus main.cpp)
target_link_libraries(uin-campus PRIVATE uin::core uincampus_options)
install(TARGETS uin-campus RUNTIME DESTINATION bin)
