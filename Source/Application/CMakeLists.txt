cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

file(
	GLOB_RECURSE SUBDIRECTORIES 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SUBDIRECTORIES})
add_executable("Space-Sim" ${SUBDIRECTORIES})

target_include_directories("Space-Sim" PRIVATE "${CMAKE_SOURCE_DIR}/Source" "${glew_SOURCE_DIR}")
target_link_libraries("Space-Sim" PUBLIC glfw glm::glm spdlog libglew_static Imgui)