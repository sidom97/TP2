# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usagers2/jaroyb/Bureau/INF8601/TP2/TP2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usagers2/jaroyb/Bureau/INF8601/TP2/TP2/build

# Utility rule file for remise.

# Include any custom commands dependencies for this target.
include CMakeFiles/remise.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/remise.dir/progress.make

CMakeFiles/remise:
	cd /usagers2/jaroyb/Bureau/INF8601/TP2/TP2 && zip --must-match -r /usagers2/jaroyb/Bureau/INF8601/TP2/TP2/build/remise.zip source/*.c source/kernel/*.cl include/*.h CMakeLists.txt .clang-format README.pdf

remise: CMakeFiles/remise
remise: CMakeFiles/remise.dir/build.make
.PHONY : remise

# Rule to build all files generated by this target.
CMakeFiles/remise.dir/build: remise
.PHONY : CMakeFiles/remise.dir/build

CMakeFiles/remise.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/remise.dir/cmake_clean.cmake
.PHONY : CMakeFiles/remise.dir/clean

CMakeFiles/remise.dir/depend:
	cd /usagers2/jaroyb/Bureau/INF8601/TP2/TP2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usagers2/jaroyb/Bureau/INF8601/TP2/TP2 /usagers2/jaroyb/Bureau/INF8601/TP2/TP2 /usagers2/jaroyb/Bureau/INF8601/TP2/TP2/build /usagers2/jaroyb/Bureau/INF8601/TP2/TP2/build /usagers2/jaroyb/Bureau/INF8601/TP2/TP2/build/CMakeFiles/remise.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/remise.dir/depend

