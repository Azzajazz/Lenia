cmake_minimum_required(VERSION 3.16)

project(glad LANGUAGES C)

add_library(
	glad
	src/glad.c
)

target_include_directories(
	glad
	PRIVATE include
)