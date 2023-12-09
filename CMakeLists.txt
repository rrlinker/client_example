cmake_minimum_required(VERSION 3.14)

project(
    client_example
    VERSION 0.1
    DESCRIPTION "Example of using Remote Run-time Linker client library."
    LANGUAGES CXX
)

set(SOURCE_FILES
    "main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC ws2_32 librrlclient librrlcom
)
