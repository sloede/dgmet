#!/bin/bash

# This script 'hopefully' removes all files that were generated during the CMake
# build process, leaving the build directory practically empty

# Set files/directories to remove
to_remove="CMakeCache.txt CMakeFiles Makefile cmake_install.cmake Doxyfile"

printf "Making 'distclean'... "

# Remove all files/directory listed above
for i in $to_remove; do
  find . -name "$i" -print0 | xargs -0 rm -rf
done

# Remove html and latex directories in doc/ (if existing)
rm -rf doc/html
rm -rf doc/latex

# Furthermore, remove empty directories (these could be left-overs from the
# build process as well)
find . -type d -empty -print0 | xargs -0 rmdir

echo "done."
