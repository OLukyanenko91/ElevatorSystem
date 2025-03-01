add_library(Logger STATIC
    Logger.cpp
    Logger.hpp

)

find_package(fmt REQUIRED)

add_subdirectory(libP7Client_v5.6)

target_include_directories(Logger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libP7Client_v5.6/Headers
)

target_link_libraries(Logger PRIVATE p7)
target_link_libraries(Logger PRIVATE Settings)
target_link_libraries(Logger PRIVATE fmt::fmt)
