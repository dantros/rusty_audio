cmake_minimum_required(VERSION 3.20)

project(miniaudio_lib_project C)

add_library(miniaudio STATIC
    "miniaudio.c"
)
set_property(TARGET miniaudio PROPERTY CXX_STANDARD 11)
target_include_directories(miniaudio PRIVATE
    "../miniaudio"
)
