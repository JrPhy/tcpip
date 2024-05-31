cmake_minimum_required(VERSION 3.16) # 決定 cmake 版本
project(tcpip) # 專案名稱
find_package(Threads REQUIRED)
add_executable(server_thread server_thread.c) # 把那些檔案編成執行檔
add_executable(client_thread client_thread.c) # 把那些檔案編成執行檔
set_target_properties(server_thread client_thread PROPERTIES
    COMPILE_FLAGS "-pthread"
    LINK_FLAGS "-pthread"
)
