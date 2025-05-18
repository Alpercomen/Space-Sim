cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

include(FetchContent)

set(GLFW_URL https://github.com/glfw/glfw.git)

FetchContent_Declare(
	glfw
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY ${GLFW_URL}
	GIT_TAG 3.3.9
	GIT_SHALLOW TRUE
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable GLFW Examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable GLFW Tests" FORCE)

FetchContent_MakeAvailable(glfw)