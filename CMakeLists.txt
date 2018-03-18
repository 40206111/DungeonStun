cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Assets URL and download path
set(MY_URL "https://docs.google.com/uc?export=download&id=14nYLfxq-3qudCQ5lb_hY2KTZZFJ60vY6")
set(MY_DOWNLOAD_PATH "${CMAKE_BINARY_DIR}/tmp/assets.zip")

project(Dungeon_Stun)

### Setup Directories ###
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Dependencies ###
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

### Download Assets ###
if (NOT "${MY_DOWNLOAD_PATH}")
	file(DOWNLOAD "${MY_URL}" "${MY_DOWNLOAD_PATH}" )
endif()
# Extract Assets
execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf "${MY_DOWNLOAD_PATH}"
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

### Main Project ###
file(GLOB_RECURSE SOURCES Code/*.cpp Code/*.h)
add_executable(NINE_TO_DIE ${SOURCES})
target_include_directories(NINE_TO_DIE PRIVATE ${SFML_INCS})
target_link_libraries(NINE_TO_DIE sfml-graphics)
