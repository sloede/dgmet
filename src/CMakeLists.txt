CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Add include directories for linker
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Set source files
SET(SRC_EXE
  ${dgmet_src_dir}/dgmet.cpp
)

# Create executable
ADD_EXECUTABLE(dgmet ${SRC_EXE})
