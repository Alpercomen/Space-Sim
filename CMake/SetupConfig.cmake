function(SetupConfig)
	if(WIN32)
		add_compile_definitions(SPACESIM_WINDOWS)
	endif()

	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		add_compile_definitions(SPACESIM_DEBUG)
	endif()

	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_compile_definitions(SPACESIM_RELEASE)
	endif()
endfunction()