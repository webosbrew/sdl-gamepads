cmake_minimum_required(VERSION 3.16)
project(sdl_gamepads C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
find_package(Freetype REQUIRED)
find_package(Fontconfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)

add_subdirectory(third_party/lvgl EXCLUDE_FROM_ALL)

target_include_directories(lvgl SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(lvgl SYSTEM PRIVATE ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(lvgl PRIVATE ${SDL2_LIBRARIES} ${FREETYPE_LIBRARIES})
target_compile_definitions(lvgl PUBLIC LV_CONF_PATH=../../../src/lvgl/lv_conf.h)

add_executable(sdl_gamepads)

target_include_directories(sdl_gamepads SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS} PUBLIC src)
target_link_libraries(sdl_gamepads PRIVATE ${SDL2_LIBRARIES} Fontconfig::Fontconfig Freetype::Freetype lvgl)

add_subdirectory(src)