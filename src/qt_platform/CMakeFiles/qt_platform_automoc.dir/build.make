# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zju/program/github/curve-design

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zju/program/github/curve-design

# Utility rule file for qt_platform_automoc.

# Include the progress variables for this target.
include src/qt_platform/CMakeFiles/qt_platform_automoc.dir/progress.make

src/qt_platform/CMakeFiles/qt_platform_automoc:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Automoc for target qt_platform"
	cd /home/zju/program/github/curve-design/src/qt_platform && /usr/bin/cmake -E cmake_automoc /home/zju/program/github/curve-design/src/qt_platform/CMakeFiles/qt_platform_automoc.dir/ Release

qt_platform_automoc: src/qt_platform/CMakeFiles/qt_platform_automoc
qt_platform_automoc: src/qt_platform/CMakeFiles/qt_platform_automoc.dir/build.make
.PHONY : qt_platform_automoc

# Rule to build all files generated by this target.
src/qt_platform/CMakeFiles/qt_platform_automoc.dir/build: qt_platform_automoc
.PHONY : src/qt_platform/CMakeFiles/qt_platform_automoc.dir/build

src/qt_platform/CMakeFiles/qt_platform_automoc.dir/clean:
	cd /home/zju/program/github/curve-design/src/qt_platform && $(CMAKE_COMMAND) -P CMakeFiles/qt_platform_automoc.dir/cmake_clean.cmake
.PHONY : src/qt_platform/CMakeFiles/qt_platform_automoc.dir/clean

src/qt_platform/CMakeFiles/qt_platform_automoc.dir/depend:
	cd /home/zju/program/github/curve-design && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zju/program/github/curve-design /home/zju/program/github/curve-design/src/qt_platform /home/zju/program/github/curve-design /home/zju/program/github/curve-design/src/qt_platform /home/zju/program/github/curve-design/src/qt_platform/CMakeFiles/qt_platform_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/qt_platform/CMakeFiles/qt_platform_automoc.dir/depend

