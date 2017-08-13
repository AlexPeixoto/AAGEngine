cmake_minimum_required (VERSION 3.0)
project (AAGEngine)

# Find source files
file(GLOB SOURCES *.cpp)

# Include header files
include_directories(.)
include_directories("../../SFML-2.1/include")

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

#link_directories("../../SFML-2.1/lib")

find_library ( SFML_AUDIO NAMES sfml-audio PATHS D:/Developer/SFML-2.1/lib )
find_library ( SFML_GRAPHICS NAMES sfml-graphics PATHS D:/Developer/SFML-2.1/lib )
find_library ( SFML_MAIN NAMES sfml-main PATHS D:/Developer/SFML-2.1/lib )
find_library ( SFML_SYSTEM NAMES sfml-system PATHS D:/Developer/SFML-2.1/lib )
find_library ( SFML_WINDOW NAMES sfml-window PATHS D:/Developer/SFML-2.1/lib )

target_link_libraries(${PROJECT_NAME} ${SFML_AUDIO} ${SFML_GRAPHICS} ${SFML_MAIN} ${SFML_SYSTEM} ${SFML_WINDOW})
