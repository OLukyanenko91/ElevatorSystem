cmake_minimum_required(VERSION 3.10)

project(ElevatorSystem VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/Settings)
add_subdirectory(src/Logger)

set(PROJECT_SOURCES
        main.cpp
        version.hpp
        src/Elevator/Elevator.hpp src/Elevator/Elevator.cpp
        src/Manager.hpp src/Manager.cpp
        src/Service.hpp src/Service.cpp
        src/Floor.hpp src/Floor.cpp
)

add_executable(ElevatorSystem
               ${PROJECT_SOURCES})

configure_file(
   ${CMAKE_SOURCE_DIR}/version.hpp.in
   ${CMAKE_BINARY_DIR}/version.hpp
)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

target_link_libraries(ElevatorSystem PRIVATE Logger)
target_link_libraries(ElevatorSystem PRIVATE Settings)
target_link_libraries(ElevatorSystem PRIVATE p7)
