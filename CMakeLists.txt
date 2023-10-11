cmake_minimum_required(VERSION 3.12)
project(OpenGL)

# Find the packages for OpenGL and GLFW
find_package(OpenGL REQUIRED)

file(GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)


# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set(INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Glad)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIRS})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LIBS
        glfw
        OpenGL::GL
        dl)
    # Copy "basic.shader" to the build directory
    file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIBS
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/lib/glfw3.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/lib/glew32s.lib
        OpenGL::GL)

    # Copy "basic.shader" to the build directory
    file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR}/Debug)
endif()
# Link OpenGL and GLFW libraries to your project
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${LIBS})

# Set C++ standard to C++11 or higher
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)