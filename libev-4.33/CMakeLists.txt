cmake_minimum_required(VERSION 3.10)

# 定义项目信息
project(libev LANGUAGES C)

# 设置版本信息
set(PROJECT_VERSION_MAJOR 4)
set(PROJECT_VERSION_MINOR 33)
#set(PROJECT_VERSION_PATCH 0)
#set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

# 设置编译选项
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置包信息
set(PACKAGE "libev")
set(PACKAGE_NAME "libev")
set(PACKAGE_VERSION "${PROJECT_VERSION}")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}")
set(PACKAGE_URL "http://software.schmorp.de/pkg/libev.html")
set(PACKAGE_BUGREPORT "")
set(VERSION "${PROJECT_VERSION}")

# 添加编译定义
option(EV_USE_EPOLL "Enable epoll backend" ON)
option(EV_USE_KQUEUE "Enable kqueue backend" OFF)
option(EV_USE_SELECT "Enable select backend" ON)
option(EV_USE_POLL "Enable poll backend" ON)

# 基本定义
# add_definitions(
#     -DEV_STANDALONE=0
#     -DEV_COMPAT3=0
#     -DEV_VERIFY=0
#     -DEV_MULTIPLICITY=0
# )

if(EV_USE_EPOLL)
    add_definitions(-DEV_USE_EPOLL=1)
endif()

if(EV_USE_KQUEUE)
    add_definitions(-DEV_USE_KQUEUE=1)
endif()

if(EV_USE_SELECT)
    add_definitions(-DEV_USE_SELECT=1)
endif()

if(EV_USE_POLL)
    add_definitions(-DEV_USE_POLL=1)
endif()

# 启用多线程支持（强制定义 EV_MULTIPLICITY）
add_definitions(-DEV_MULTIPLICITY=1)


file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# 包含配置检查文件
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigureChecks.cmake)
configure_file(
  ${CMAKE_SOURCE_DIR}/config.h.in
  ${CMAKE_BINARY_DIR}/config.h
)
include_directories(${CMAKE_BINARY_DIR})

# 添加源文件
# set(SOURCES
#     ev.c
#     ev_epoll.c
#     ev_kqueue.c
#     ev_poll.c
#     ev_select.c
#     ev_win32.c
#     ev_iouring.c
#     ev_linuxaio.c
#     ev_port.c
#     event.c
# )
set(SOURCES ev.c event.c)

# 添加头文件目录
include_directories(${PROJECT_SOURCE_DIR})

# 生成静态库和动态库
add_library(libev_static STATIC ${SOURCES})
add_library(libev_shared SHARED ${SOURCES})

# 设置输出名称
set_target_properties(libev_static PROPERTIES OUTPUT_NAME ev)
set_target_properties(libev_shared PROPERTIES OUTPUT_NAME ev)

# 安装规则
install(TARGETS libev_static libev_shared
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(FILES ev.h ev++.h DESTINATION include)# 创建cmake目录（如果不存在）
