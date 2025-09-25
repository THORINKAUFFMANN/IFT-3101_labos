cmake_minimum_required(VERSION 3.10)

project(opengl_circle_app)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} src)

file(GLOB SOURCES "src/*.cpp")

add_executable(opengl_circle_app ${SOURCES})

target_link_libraries(opengl_circle_app ${OPENGL_LIBRARIES})