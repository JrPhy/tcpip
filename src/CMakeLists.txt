add_executable(server_thread server_thread.c) # 把那些檔案編成執行檔
add_executable(client_thread client_thread.c) # 把那些檔案編成執行檔
add_library(add STATIC add.c) # 把 add.c 編成 libadd.a
add_library(divide SHARED divide.c) # 把 divide.c 編成 libdivide.so
set_target_properties(server_thread client_thread PROPERTIES
    COMPILE_FLAGS "-pthread"
    LINK_FLAGS "-pthread"
)
include_directories(${PROJECT_NAME})
link_directories(${PROJECT_NAME})
install(TARGETS server_thread client_thread add divide
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build/install/bin
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build/install/lib
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build/install/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build/install/include
    )
