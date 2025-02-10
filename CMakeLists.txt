cmake_minimum_required(VERSION 3.10)

project(ElevatorSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Settings)
add_subdirectory(Logger)

set(PROJECT_SOURCES
        main.cpp
)

add_executable(ElevatorSystem
               ${PROJECT_SOURCES})

target_link_libraries(ElevatorSystem PRIVATE Logger)
target_link_libraries(ElevatorSystem PRIVATE Settings)
target_link_libraries(ElevatorSystem PRIVATE p7)
