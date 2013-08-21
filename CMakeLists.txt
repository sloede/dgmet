CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

################################################################################
# Set project name, description & set language to C++ (disables C compiler)
PROJECT(DGMET CXX)
SET(PROJECT_DESCRIPTION
    "A testbed for experimenting with discontinuous Galerkin methods.")

################################################################################
# Warn user when attempting an in-source build
IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(WARNING "In-source build detected. It is highly recommended to use "
          "a dedicated build directory that is outside the source directory.")
ENDIF ()

################################################################################
# Find all possibly needed packages
FIND_PACKAGE(Git QUIET) # Needed for git hash tag

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
# Create custom target 'distclean' to remove all files created during the 
# CMake build process
ADD_CUSTOM_TARGET(distclean
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_SOURCE_DIR}/aux/distclean.sh
)

################################################################################
# Create custom target 'doc' to generate Doxygen documentation in 'docs/'
IF (GIT_FOUND)
  EXECUTE_PROCESS(
    COMMAND git log -1 --format="%H"
    OUTPUT_VARIABLE PROJECT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
ELSE ()
  SET(PROJECT_VERSION "")
ENDIF ()

################################################################################
# Set output directories for the finished results
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

################################################################################
# Set directory for source files
SET(dgmet_src_dir ${CMAKE_SOURCE_DIR}/src)

################################################################################
# Add subdirectories with own CMakeLists.txt
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/src)
