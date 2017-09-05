cmake_minimum_required(VERSION 3.0)

project(crayon)

add_library(crayon INTERFACE)
target_include_directories(crayon INTERFACE $[CMAKE_CURRENT_SOURCE_DIR})