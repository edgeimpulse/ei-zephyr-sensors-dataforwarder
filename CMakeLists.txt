cmake_minimum_required(VERSION 3.20.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ei-zephyr-data-collection
    DESCRIPTION "Edge Impulse Data forwarder firmware for Zephyr OS"
    VERSION 1.0.0
    LANGUAGES C CXX ASM
    )

# Needed for colorful output
zephyr_compile_options(-fdiagnostics-color=always)

# add all sources to the project
target_sources(app PRIVATE src/main.cpp)
