CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

################################################################################
# Add include directories for linker
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/${INCLUDE_DIR})

################################################################################
# Set library files
SET(src_lib
    ${SRC_DIR_ABS}/dgmetlib.cpp)

################################################################################
# Create library target
ADD_LIBRARY(${LIB_TARGET} ${src_lib})
SET_TARGET_PROPERTIES(${LIB_TARGET} PROPERTIES OUTPUT_NAME ${LIB_NAME})

################################################################################
# Set source files and libraries
SET(src_exe
    ${SRC_DIR_ABS}/dgmet.cpp)
SET(libs_exe
    ${LIB_TARGET})

################################################################################
# Create executable
ADD_EXECUTABLE(${BIN_TARGET} ${src_exe})
SET_TARGET_PROPERTIES(${BIN_TARGET} PROPERTIES OUTPUT_NAME ${BIN_NAME})

################################################################################
# Link library to executable
TARGET_LINK_LIBRARIES(${BIN_TARGET} ${libs_exe})
