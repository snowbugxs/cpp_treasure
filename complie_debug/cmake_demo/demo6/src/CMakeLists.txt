include_directories(${PROJECT_SOURCT_DIR}/libhello)
#link_directories(${PROJECT_BINARY_DIR}/lib)

set(APP_SRC main.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(hello ${APP_SRC})
target_link_libraries(hello libhello)


#set_target_properties(libhello PROPERTIES OUTPUT_NAME "hello")
