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
        src/Service/Service.hpp src/Service/Service.cpp
        src/Service/MAVLinkHandler.hpp src/Service/MAVLinkHandler.cpp
        src/Service/UDPLink.hpp src/Service/UDPLink.cpp
        src/Floor.hpp src/Floor.cpp
        src/Common.hpp
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

target_include_directories(ElevatorSystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Service/MAVLink/include
)
