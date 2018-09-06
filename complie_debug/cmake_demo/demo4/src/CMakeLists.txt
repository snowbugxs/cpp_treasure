include_directories(${PROJECT_SOURCT_DIR}/libhello)
set(APP_SRC main.c)
add_executable(hello ${APP_SRC})
target_link_libraries(hello libhello)


#set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")
