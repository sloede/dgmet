CMAKE_MINIMUM_REQUIRED(2.8)

# Add include directories for linker
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Set source files for library
SET(SRC_LIB
  ${CMAKE_SOURCE_DIR}/src/aux/constants.hpp
  ${CMAKE_SOURCE_DIR}/src/aux/types.hpp
  ${CMAKE_SOURCE_DIR}/src/aux/globals.hpp
)

# Create library with all of DGMET's functionality
ADD_LIBRARY(dgmet ${SRC_LIB})

# Set source files for executable
SET(SRC_EXE ${CMAKE_SOURCE_DIR}/src/dgmet.cpp)

# Create executable
ADD_EXECUTABLE(dgmet ${SRC_EXE})
