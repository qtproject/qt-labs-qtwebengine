cmake_minimum_required(VERSION 3.19)

if(NOT DEFINED WEBENGINE_ROOT_SOURCE_DIR)
    get_filename_component(WEBENGINE_ROOT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../.." REALPATH)
endif()
if (NOT DEFINED WEBENGINE_ROOT_BUILD_DIR)
    get_filename_component(WEBENGINE_ROOT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../.." REALPATH)
endif()

include(${WEBENGINE_ROOT_SOURCE_DIR}/.cmake.conf)
include(${WEBENGINE_ROOT_SOURCE_DIR}/cmake/Functions.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${WEBENGINE_ROOT_SOURCE_DIR}/cmake")

project(QtWebEngineConfigure
    VERSION "${QT_REPO_MODULE_VERSION}"
    LANGUAGES CXX C)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core)

set(buildDir ${CMAKE_CURRENT_BINARY_DIR})
configure_gn_toolchain(host ${TEST_architecture_arch} ${TEST_architecture_arch}
    ${WEBENGINE_ROOT_SOURCE_DIR}/src/core/configure/BUILD.toolchain.gn.in
    ${buildDir}/host_toolchain
)
install(FILES ${buildDir}/host_toolchain/BUILD.gn
    DESTINATION ${WEBENGINE_ROOT_BUILD_DIR}/src/core/host_toolchain
    )
get_v8_arch(GN_V8_HOST_CPU ${GN_TARGET_CPU})
configure_gn_toolchain(v8 ${GN_V8_HOST_CPU} ${GN_TARGET_CPU}
    ${WEBENGINE_ROOT_SOURCE_DIR}/src/core/configure/BUILD.toolchain.gn.in
    ${buildDir}/v8_toolchain)
install(FILES ${buildDir}/v8_toolchain/BUILD.gn
    DESTINATION ${WEBENGINE_ROOT_BUILD_DIR}/src/core/v8_toolchain
)
