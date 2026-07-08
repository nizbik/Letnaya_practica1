# CMakeLists.txt - корневой файл сборки проекта.
# Зубехин Никита
# МК-101
 

cmake_minimum_required(VERSION 3.10)
project(letmaya_practica_1 C)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(MyFunctions)


if(NOT DEFINED N)
    set(N 1024)
endif()
add_definitions(-DN=${N})


add_subdirectory(lib)
add_subdirectory(app)