
cmake_minimum_required(VERSION 3.18.0)

project(Gn
    DESCRIPTION "Meta-build system"
    HOMEPAGE_URL "https://gn.googlesource.com/gn/"
    LANGUAGES CXX C
)

set(GN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/gn)
set(GN_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gn)
set(GN_EXECUTABLE ${GN_BINARY_DIR}/gn)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")

find_package(Python2 REQUIRED)
find_package(Ninja 1.7.2 REQUIRED)

file(MAKE_DIRECTORY ${GN_BINARY_DIR})
add_custom_command(
    OUTPUT ${GN_EXECUTABLE}
    WORKING_DIRECTORY ${GN_BINARY_DIR}
    COMMAND ${Python2_EXECUTABLE} ${GN_SOURCE_DIR}/build/gen.py
        --no-last-commit-position
        --out-path .
        --cc ${CMAKE_C_COMPILER}
        --cxx ${CMAKE_CXX_COMPILER}
        --ld ${CMAKE_CXX_COMPILER}
    COMMAND Ninja::ninja gn
    VERBATIM
    USES_TERMINAL
    COMMAND_EXPAND_LISTS
)
add_custom_target(gn ALL DEPENDS ${GN_EXECUTABLE})
install(FILES ${GN_EXECUTABLE}
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
        DESTINATION bin)