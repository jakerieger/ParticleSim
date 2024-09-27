cmake_minimum_required(VERSION 3.29)
project(ParticleSim)

add_subdirectory(OpenGLTK)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLTK/ThirdParty
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLTK/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

set(SOURCES
        Source/main.cpp
)

add_executable(ParticleSim
        ${THIRD_PARTY_SRCS}
        ${SOURCES}
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(ParticleSim PRIVATE
        glfw
        glm::glm-header-only
        OpenGLTK
)

add_custom_command(TARGET ParticleSim PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data)