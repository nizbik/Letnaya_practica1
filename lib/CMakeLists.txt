# CMakeLists.txt - настройки сборки библиотеки.
#Зубехин Никита
# МК-101

get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}/src" LIB_SOURCES)

add_library(letnaya_lib ${LIB_SOURCES})

target_include_directories(letnaya_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")