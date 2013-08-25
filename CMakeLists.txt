CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# This is the main CMake configuration file for this project

################################################################################
# Set project name, description & set language to C++ (disables C compiler)
PROJECT(DGMET CXX)
SET(PROJECT_DESCRIPTION
    "A testbed for experimenting with discontinuous Galerkin methods.")

################################################################################
# Configure paths
# Module path for custom CMake modules
SET(CMAKE_DIR "cmake")
# Output path for binaries
SET(BIN_DIR "bin")
# Output path for libraryes & archives
SET(LIB_DIR "lib")
# Directory with source files
SET(SRC_DIR "src")
# Directory with documentation
SET(DOC_DIR "doc")
# Directory with utilities
SET(UTILS_DIR "utils")

################################################################################
# Configure targets
SET(DOC_TARGET "doc")
SET(DISTCLEAN_TARGET "distclean")

################################################################################
# NO NEED TO CHANGE ANYTHING BEYOND THIS LINE
################################################################################


################################################################################
# Set paths
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${LIB_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${LIB_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BIN_DIR})

################################################################################
# Warn user when attempting an in-source build
IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(WARNING "In-source build detected. It is highly recommended to use "
          "a dedicated build directory that is outside the source directory.")
ENDIF ()

################################################################################
# Detect build type
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  MESSAGE(STATUS "Build type is 'Debug'.")
ELSEIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  MESSAGE(STATUS "Build type is 'Release'.")
ELSE ()
  MESSAGE(FATAL_ERROR "Unsupported build type '${CMAKE_BUILD_TYPE}'. "
          "Must be either 'Debug' or 'Release'.")
ENDIF ()

################################################################################
# Check for compiler and set compiler flags 
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # Configure for clang
  # Check if compiler version fully supports C++11
  EXECUTE_PROCESS(
      COMMAND "bash" "-c"
              "${CMAKE_CXX_COMPILER} --version | head -n 1 | awk '{print $3}'"
      OUTPUT_VARIABLE compiler_version OUTPUT_STRIP_TRAILING_WHITESPACE)
  IF (${compiler_version} VERSION_LESS 3.3)
    MESSAGE(FATAL_ERROR "Need clang version >= 3.3 for full C++11 support. "
            "Detected version is '${compiler_version}'.")
  ENDIF ()

  # Set compiler flags
  # Default
  SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
  # Debug
  SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  # Release
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # Configure for gcc
  # Check if compiler version fully supports C++11
  EXECUTE_PROCESS(
      COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
      OUTPUT_VARIABLE compiler_version OUTPUT_STRIP_TRAILING_WHITESPACE)
  IF (${compiler_version} VERSION_LESS 4.8.1)
    MESSAGE(FATAL_ERROR "Need gcc/g++ version >= 4.8.1 for full C++11 support. "
            "Detected version is '${compiler_version}'.")
  ENDIF ()

  # Set compiler flags
  # Default
  SET(CMAKE_CXX_FLAGS "-std=c++11")
  # Debug
  SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
  # Release
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
ELSE ()
  # Abort for unrecognized compilers             
  MESSAGE(FATAL_ERROR "Unrecognized compiler '${CMAKE_CXX_COMPILER_ID}'."
          "Use clang, gcc or add a new compiler to CMakeLists.txt.")
ENDIF ()

################################################################################
# Create custom target '${DISTCLEAN_TARGET}' to remove all files created during
# the CMake build process
ADD_CUSTOM_TARGET(${DISTCLEAN_TARGET}
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_SOURCE_DIR}/${UTILS_DIR}/distclean.sh)


################################################################################
# Add subdirectories with own CMakeLists.txt
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/${DOC_DIR})
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/${SRC_DIR})
