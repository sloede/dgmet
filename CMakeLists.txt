CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

################################################################################
# Set project name
PROJECT(DGMET)

################################################################################
# Warn user when attempting an in-source build
IF ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(WARNING "In-source build detected! It is highly recommended to use "
          "a dedicated build directory that is outside the source directory.")
ENDIF()

################################################################################
# Set compiler flags 
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
  ENDIF()

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
  ENDIF()

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
ENDIF()

################################################################################
# Create custom target 'distclean' to remove all files created during the 
# CMake build process
ADD_CUSTOM_TARGET(distclean
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_SOURCE_DIR}/aux/distclean.sh
)

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
