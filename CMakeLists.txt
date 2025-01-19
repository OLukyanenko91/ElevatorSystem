cmake_minimum_required(VERSION 3.10)

project(ElevatorSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Logger)

set(PROJECT_SOURCES
        main.cpp
        Logger/Logger.hpp
        Logger/Logger.cpp
)

add_executable(ElevatorSystem
               ${PROJECT_SOURCES})

target_link_libraries(ElevatorSystem PRIVATE p7)

include(GNUInstallDirs)
target_include_directories(ElevatorSystem PRIVATE libP7Client_v5.6/Headers)

install(TARGETS ElevatorSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
