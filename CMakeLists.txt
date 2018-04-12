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


#----------
# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D" EXCLUDE_FROM_ALL)
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
#----------



### Download Assets ###
file(DOWNLOAD "${MY_URL}" "${MY_DOWNLOAD_PATH}" )
# Extract Assets
execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf "${MY_DOWNLOAD_PATH}"
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)



#------------------
#### Add Engine and our own library projects####
####
file(GLOB_RECURSE SOURCE_FILES engine/src/*.cpp engine/src/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/src/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_maths" INTERFACE ${SFML_INCS})

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES engine/lib_tile_level_loader/*.cpp engine/lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## ECM lib
file(GLOB_RECURSE SOURCE_FILES engine/lib_ecm/*.cpp engine/lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/engine/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)
#-----------------



### Main Project ###
file(GLOB_RECURSE SOURCES Code/*.cpp Code/*.h)
file(GLOB_RECURSE SCENES Code/scenes/*.cpp Code/scenes/*.h)
add_executable(NINE_TO_DIE ${SOURCES})
source_group("Scenes" FILES ${SCENES})
target_include_directories(NINE_TO_DIE PRIVATE ${SFML_INCS})
target_link_libraries(NINE_TO_DIE sfml-graphics)

#set working directory to build directory
set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)




#####EXE STUFF#######
#Install directory within build folder, so it doesn't go into /lib or program-files
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install/")
#Installer.exe/zip built into /installer
SET(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/installer/")
#Install component for runtime dlls and stuff
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE) #stop this happening on non-release builds
INCLUDE(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION "bin/" CONFIGURATIONS Release COMPONENT SYSTEM_CMPT)
#Install component for resources
install(DIRECTORY "${CMAKE_BINARY_DIR}/Assets" DESTINATION "bin/" CONFIGURATIONS Release COMPONENT RESOURCES_CMPT)
#We disabled SFML's INSTALL component as it brings along junk, so we gotta make one ourselves
install(DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/" DESTINATION "bin" CONFIGURATIONS Release COMPONENT SFML_CMPT FILES_MATCHING PATTERN "*.dll" )
#Main Install target
install(TARGETS NINE_TO_DIE DESTINATION "bin" CONFIGURATIONS Release COMPONENT DUNGEON_STUN_CMPT)

#Tell CPack about the libs and resources install components
set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} RESOURCES_CMPT SFML_CMPT SYSTEM_CMPT DUNGEON_STUN_CMPT)
set(CPACK_COMPONENT_DUNGEON_STUN_CMPT_DEPENDS RESOURCES_CMPT SFML_CMPT SYSTEM_CMPT)
set(CPACK_COMPONENT_RESOURCES_CMPT_REQUIRED TRUE)
set(CPACK_COMPONENT_SFML_CMPT_REQUIRED TRUE)
set(CPACK_COMPONENT_SYSTEM_CMPT_REQUIRED TRUE)
set(CPACK_COMPONENT_DUNGEON_STUN_CMPT_DISPLAY_NAME "Nine To Die")

IF(WIN32)
  set(CPACK_GENERATOR NSIS)
  set(CPACK_NSIS_COMPONENT_INSTALL ON)
  set(CPACK_NSIS_HELP_LINK "https://github.com/40206111/DungeonStun")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/40206111/DungeonStun")
  set(CPACK_NSIS_CONTACT "https://github.com/40206111/")
  set(CPACK_NSIS_MUI_ICON "${CMAKE_BINARY_DIR}/Assets/imgs/icon.ico")
ELSE()
  set(CPACK_GENERATOR ZIP)
ENDIF(WIN32)


set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Games eng coursework game")
set(CPACK_PACKAGE_VENDOR "Groupie")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)
