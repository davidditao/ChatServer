cmake_minimum_required(VERSION 3.0)
project(main)

# 配置编译选项
set(CMAKE_CXX_FLAGES ${CMAKE_CXX_FLAGES} -g)

# 配置头文件搜索路径
# include_directories()
# 配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 把 . 路径下的所有源文件名字放入变量SRC_LIST里面
# aux_source_directory(. SRC_LIST)

# 设置可执行文件最终存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件server, 由 SRC_LIST 变量所定义的源文件而来
add_executable(server ${SRC_LIST})
# 表示server这个程序,需要连接什么库
target_link_libraries(server muduo_net muduo_base pthread)