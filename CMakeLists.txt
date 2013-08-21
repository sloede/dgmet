CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(DGMET)

# Add subdirectories with own CMakeLists.txt
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src)

# Add include directories for linker
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
