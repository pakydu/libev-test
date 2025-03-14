
cmake_minimum_required(VERSION 3.10)
project(io_ev C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 添加系统定义
if(UNIX)
    add_definitions(
        -D_GNU_SOURCE
        -D_POSIX_C_SOURCE=200809L
        -D_XOPEN_SOURCE=700
        -D_DEFAULT_SOURCE
    )
endif()
add_compile_options( -static )

include_directories(/home/pakydu/works/libev/libev-4.33/)
link_directories(/home/pakydu/works/libev/libev-4.33/build)
link_libraries( ev m pthread)

aux_source_directory(./ src_list)


# 添加可执行文件
add_executable(${PROJECT_NAME} ${src_list})

# 查找 libev
# find_library(LIBEV ev)
# if(NOT LIBEV)
#     message(FATAL_ERROR "libev not found")
# endif()

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/..)


# 链接 libev
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBEV})

# 添加编译选项
target_compile_definitions(${PROJECT_NAME} PRIVATE
    EV_STANDALONE=0
    EV_COMPAT3=0
    EV_VERIFY=0
    EV_MULTIPLICITY=0
)
