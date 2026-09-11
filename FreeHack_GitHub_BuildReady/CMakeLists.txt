cmake_minimum_required(VERSION 3.21)
project(FreeHack VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK is not set. Install/configure the Geode SDK first.")
endif()

add_library(${PROJECT_NAME} SHARED
    src/FreeHack.cpp
)

setup_geode_mod(${PROJECT_NAME})
