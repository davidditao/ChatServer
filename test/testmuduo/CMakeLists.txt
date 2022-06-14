cmake_minimum_required(VERSION 3.0) # 要求 cmake 最低的版本号
project (main) # 定义当前工程名字

# 配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)  

# 配置头文件的搜索路径
# include_directories()

#配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

# 把 . (当前)路径下的所有源文件名字放入变量 SRC_LIST 里面
# aux_source_directory(. SRC_LIST)

# 设置可执行文件最终存储的路径 /bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 表示生成可执行文件server，由SRC_LIST变量所定义的源文件编译而来
add_executable(server ${SRC_LIST})

# 表示生成server这个目标程序，需要连接 muduo_net muduo_base pthread 这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)


