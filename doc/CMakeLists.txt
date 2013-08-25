CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# This script finds all necessary packages and creates a custom target for the
# generation of the Doxygen documentation

################################################################################
# Create custom target '${DOC_TARGET}' to generate Doxygen documentation in
# '${DOC_DIR}'
OPTION(BUILD_DOCUMENTATION
    "Use Doxygen to automatically generate HTML documentation in '${DOC_DIR}/'."
    ON)

################################################################################
# If documentation is enabled, create documentation target
IF (BUILD_DOCUMENTATION)
# Doxygen is mandatory
  FIND_PACKAGE(Doxygen REQUIRED)

# Generate project version number if possible
  FIND_PACKAGE(Git QUIET)
  IF (GIT_FOUND)
    EXECUTE_PROCESS(COMMAND git log -1 --format="%H"
                    OUTPUT_VARIABLE project_number
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
  ELSE ()
    SET(project_number "")
  ENDIF ()

# Check if DOT was found
  IF (DOXYGEN_DOT_FOUND)
    SET(have_dot "YES")
  ELSE ()
    SET(have_dot "NO")
  ENDIF ()

# Generate Doxygen file
  CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/${DOC_DIR}/Doxyfile.in
                 ${CMAKE_BINARY_DIR}/${DOC_DIR}/Doxyfile @ONLY)

# Add custom target for the documentation 
  ADD_CUSTOM_TARGET(
    ${DOC_TARGET} COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${DOC_DIR})
ENDIF ()

