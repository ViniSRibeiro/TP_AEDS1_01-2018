cmake_minimum_required(VERSION 3.9)
project(AIRPORT_CONTROL C)

set(CMAKE_C_STANDARD 99)

set(AIRPORT_CONTROL_SRC
        airport_control.c
        )

add_executable(AIRPORT_CONTROL ${AIRPORT_CONTROL_SRC})

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_AIRPORT_CONTROL_DEBUG")
