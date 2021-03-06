cmake_minimum_required(VERSION 3.14)

project(
    client_example
    VERSION 0.1
    DESCRIPTION "Example of using Remote Run-time Linker client library."
    LANGUAGES CXX
)

include("${CMAKE_SOURCE_DIR}/../cmake/find_libs_dir.cmake")
include("${CMAKE_SOURCE_DIR}/../cmake/find_arch.cmake")

file(GLOB SOURCE_FILES
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_directories(
    ${PROJECT_NAME}
    PRIVATE "../librrlclient/build/${ARCH}/$<CONFIG>"
    PRIVATE "../librrlcom/build/${ARCH}/$<CONFIG>"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ws2_32 librrlclient librrlcom
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE "${PROJECT_SOURCE_DIR}/.."
)
