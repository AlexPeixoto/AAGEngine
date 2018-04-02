cmake_minimum_required (VERSION 3.0)
project (AAGEngine)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

# Set Modules Dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Find source files
file(GLOB SOURCES *.cpp)

# Include header files
include_directories(.)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
	  include_directories(${SFML_INCLUDE_DIR})
	  	target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#target_link_libraries(${PROJECT_NAME} ${SFML_AUDIO} ${SFML_GRAPHICS} ${SFML_MAIN} ${SFML_SYSTEM} ${SFML_WINDOW})
