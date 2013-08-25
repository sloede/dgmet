CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Add include directories for linker
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/${INCLUDE_DIR})

# Set source files
SET(SRC_EXE
  ${CMAKE_SOURCE_DIR}/${SRC_DIR}/dgmet.cpp
)

# Create executable
ADD_EXECUTABLE(dgmet ${SRC_EXE})
