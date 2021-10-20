
set(BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(BOARD auto_gauge)

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(auto-gauge)

target_sources(app PRIVATE src/main.c)

