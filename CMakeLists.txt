cmake_minimum_required(VERSION 3.8)

project(BRACO_MECANICO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(braco
    src/main.cpp
    src/servo.cpp
    src/joystick.cpp
    src/servoSleep.cpp
)

target_link_libraries(braco
    pigpio
    pthread
)

target_include_directories(braco PUBLIC
    include 
)