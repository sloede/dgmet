# This module finds all necessary packages and creates a custom target for the
# generation of the Doxygen documentation

# Doxygen is mandatory
FIND_PACKAGE(Doxygen REQUIRED)

# Generate project version number if possible
FIND_PACKAGE(Git QUIET)
IF (GIT_FOUND)
  EXECUTE_PROCESS(COMMAND git log -1 --format="%H"
                  OUTPUT_VARIABLE PROJECT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
ELSE ()
  SET(PROJECT_VERSION "")
ENDIF ()

# Generate Doxygen file
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/aux/Doxyfile.in
               ${CMAKE_BINARY_DIR}/doc/Doxyfile @ONLY)

# Add custom target for the documentation 
ADD_CUSTOM_TARGET(doc COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc)
