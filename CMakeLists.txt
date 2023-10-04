cmake_minimum_required(VERSION 3.12)
project(OpenGL)

# Find the packages for OpenGL and GLFW
find_package(OpenGL REQUIRED)

file(GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)


# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

set(INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIRS})

# Link OpenGL and GLFW libraries to your project
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glfw
    OpenGL::GL
    dl
)

# Set C++ standard to C++11 or higher
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)