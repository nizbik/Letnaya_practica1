# CMakeLists.txt - настройки сборки основной программы.
# Зубехин Никита
# МК-101

get_all_sources("${CMAKE_CURRENT_SOURCE_DIR}/src" APP_SOURCES)

add_executable(letnaya_practica_1 ${APP_SOURCES})

target_link_libraries(letnaya_practica_1 PRIVATE letnaya_lib)