cmake_minimum_required(VERSION 3.27)
project(Clion_Qt1)


set(CMAKE_CXX_STANDARD 23)

#只和cv的配置有关
if(NOT OpenCV_DIR)
    set(OpenCV_DIR D:/opencv/opencv/mingwbuild)
endif()
message(STATUS "OpenCV_DIR = ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

include(cmake/build_func.cmake)
#
add_subdirectory(examples/template)
add_subdirectory(examples/Aliyun)
add_subdirectory(examples/stdthread)
add_subdirectory(examples/mutex)
add_subdirectory(examples/condition_variable)
add_subdirectory(examples/promise_future)
add_subdirectory(examples/packaged_task_async)