cmake_minimum_required(VERSION 3.16)

project(Lenia LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_subdirectory(vendor/glad)

link_directories(${OpenGL_LIBRARY_DIRS} vendor/libs)
include_directories(
	vendor/glad/include
	vendor/glfw/include
)

add_executable(
	testing
	Lenia/Simulation.cpp
	Lenia/Main.cpp
	Lenia/Renderer.cpp
	Lenia/GameOfLife.cpp
	Lenia/DiscreteLenia.cpp
)

target_link_libraries(
	testing
	PRIVATE glfw3
	PRIVATE glad
	PRIVATE opengl32
)