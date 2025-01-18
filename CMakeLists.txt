cmake_minimum_required(VERSION 3.16)

project(ElevatorSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Logger)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.hpp
        MainWindow.ui
        Logger/Logger.hpp
        Logger/Logger.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ElevatorSystem
                      MANUAL_FINALIZATION
                      ${PROJECT_SOURCES})
else()
    add_executable(ElevatorSystem
                   ${PROJECT_SOURCES})
endif()

target_link_libraries(ElevatorSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ElevatorSystem PRIVATE p7)

include(GNUInstallDirs)
target_include_directories(ElevatorSystem PRIVATE libP7Client_v5.6/Headers)

install(TARGETS ElevatorSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
