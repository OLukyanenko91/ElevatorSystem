add_library(Settings STATIC
    Settings.hpp
    SettingsLoader.hpp
    SettingsLoader.cpp
    Keys.hpp
)

find_package(fmt REQUIRED)

add_subdirectory(nlohmann_json)

target_include_directories(Settings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Settings PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(Settings PRIVATE fmt::fmt)
