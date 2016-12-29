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
CMAKE_SOURCE_DIR = /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release

# Include any dependencies generated for this target.
include src/alg/CMakeFiles/alg.dir/depend.make

# Include the progress variables for this target.
include src/alg/CMakeFiles/alg.dir/progress.make

# Include the compile flags for this target's objects.
include src/alg/CMakeFiles/alg.dir/flags.make

src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o: src/alg/CMakeFiles/alg.dir/flags.make
src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o: ../src/alg/curve_interp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/curve_interp.cpp.o -c /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/curve_interp.cpp

src/alg/CMakeFiles/alg.dir/curve_interp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/curve_interp.cpp.i"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/curve_interp.cpp > CMakeFiles/alg.dir/curve_interp.cpp.i

src/alg/CMakeFiles/alg.dir/curve_interp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/curve_interp.cpp.s"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/curve_interp.cpp -o CMakeFiles/alg.dir/curve_interp.cpp.s

src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.requires:
.PHONY : src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.requires

src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.provides: src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.requires
	$(MAKE) -f src/alg/CMakeFiles/alg.dir/build.make src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.provides.build
.PHONY : src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.provides

src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.provides.build: src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o

src/alg/CMakeFiles/alg.dir/Mesh.cpp.o: src/alg/CMakeFiles/alg.dir/flags.make
src/alg/CMakeFiles/alg.dir/Mesh.cpp.o: ../src/alg/Mesh.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/alg/CMakeFiles/alg.dir/Mesh.cpp.o"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/Mesh.cpp.o -c /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/Mesh.cpp

src/alg/CMakeFiles/alg.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/Mesh.cpp.i"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/Mesh.cpp > CMakeFiles/alg.dir/Mesh.cpp.i

src/alg/CMakeFiles/alg.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/Mesh.cpp.s"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/Mesh.cpp -o CMakeFiles/alg.dir/Mesh.cpp.s

src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.requires:
.PHONY : src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.requires

src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.provides: src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.requires
	$(MAKE) -f src/alg/CMakeFiles/alg.dir/build.make src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.provides.build
.PHONY : src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.provides

src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.provides.build: src/alg/CMakeFiles/alg.dir/Mesh.cpp.o

src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o: src/alg/CMakeFiles/alg.dir/flags.make
src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o: ../src/alg/GeodesicGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/GeodesicGenerator.cpp.o -c /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/GeodesicGenerator.cpp

src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/GeodesicGenerator.cpp.i"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/GeodesicGenerator.cpp > CMakeFiles/alg.dir/GeodesicGenerator.cpp.i

src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/GeodesicGenerator.cpp.s"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/GeodesicGenerator.cpp -o CMakeFiles/alg.dir/GeodesicGenerator.cpp.s

src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.requires:
.PHONY : src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.requires

src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.provides: src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.requires
	$(MAKE) -f src/alg/CMakeFiles/alg.dir/build.make src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.provides.build
.PHONY : src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.provides

src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.provides.build: src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o

src/alg/CMakeFiles/alg.dir/projection.cpp.o: src/alg/CMakeFiles/alg.dir/flags.make
src/alg/CMakeFiles/alg.dir/projection.cpp.o: ../src/alg/projection.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/alg/CMakeFiles/alg.dir/projection.cpp.o"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/projection.cpp.o -c /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/projection.cpp

src/alg/CMakeFiles/alg.dir/projection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/projection.cpp.i"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/projection.cpp > CMakeFiles/alg.dir/projection.cpp.i

src/alg/CMakeFiles/alg.dir/projection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/projection.cpp.s"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/projection.cpp -o CMakeFiles/alg.dir/projection.cpp.s

src/alg/CMakeFiles/alg.dir/projection.cpp.o.requires:
.PHONY : src/alg/CMakeFiles/alg.dir/projection.cpp.o.requires

src/alg/CMakeFiles/alg.dir/projection.cpp.o.provides: src/alg/CMakeFiles/alg.dir/projection.cpp.o.requires
	$(MAKE) -f src/alg/CMakeFiles/alg.dir/build.make src/alg/CMakeFiles/alg.dir/projection.cpp.o.provides.build
.PHONY : src/alg/CMakeFiles/alg.dir/projection.cpp.o.provides

src/alg/CMakeFiles/alg.dir/projection.cpp.o.provides.build: src/alg/CMakeFiles/alg.dir/projection.cpp.o

src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o: src/alg/CMakeFiles/alg.dir/flags.make
src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o: ../src/alg/CurveGenerator2.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/CurveGenerator2.cpp.o -c /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/CurveGenerator2.cpp

src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/CurveGenerator2.cpp.i"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/CurveGenerator2.cpp > CMakeFiles/alg.dir/CurveGenerator2.cpp.i

src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/CurveGenerator2.cpp.s"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/CurveGenerator2.cpp -o CMakeFiles/alg.dir/CurveGenerator2.cpp.s

src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.requires:
.PHONY : src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.requires

src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.provides: src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.requires
	$(MAKE) -f src/alg/CMakeFiles/alg.dir/build.make src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.provides.build
.PHONY : src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.provides

src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.provides.build: src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o

src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o: src/alg/CMakeFiles/alg.dir/flags.make
src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o: ../src/alg/CurveGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/alg.dir/CurveGenerator.cpp.o -c /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/CurveGenerator.cpp

src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alg.dir/CurveGenerator.cpp.i"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/CurveGenerator.cpp > CMakeFiles/alg.dir/CurveGenerator.cpp.i

src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alg.dir/CurveGenerator.cpp.s"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg/CurveGenerator.cpp -o CMakeFiles/alg.dir/CurveGenerator.cpp.s

src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.requires:
.PHONY : src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.requires

src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.provides: src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.requires
	$(MAKE) -f src/alg/CMakeFiles/alg.dir/build.make src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.provides.build
.PHONY : src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.provides

src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.provides.build: src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o

# Object files for target alg
alg_OBJECTS = \
"CMakeFiles/alg.dir/curve_interp.cpp.o" \
"CMakeFiles/alg.dir/Mesh.cpp.o" \
"CMakeFiles/alg.dir/GeodesicGenerator.cpp.o" \
"CMakeFiles/alg.dir/projection.cpp.o" \
"CMakeFiles/alg.dir/CurveGenerator2.cpp.o" \
"CMakeFiles/alg.dir/CurveGenerator.cpp.o"

# External object files for target alg
alg_EXTERNAL_OBJECTS =

lib/libalg.so: src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o
lib/libalg.so: src/alg/CMakeFiles/alg.dir/Mesh.cpp.o
lib/libalg.so: src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o
lib/libalg.so: src/alg/CMakeFiles/alg.dir/projection.cpp.o
lib/libalg.so: src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o
lib/libalg.so: src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o
lib/libalg.so: src/alg/CMakeFiles/alg.dir/build.make
lib/libalg.so: lib/libglobals.so
lib/libalg.so: src/alg/CMakeFiles/alg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../lib/libalg.so"
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/alg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/alg/CMakeFiles/alg.dir/build: lib/libalg.so
.PHONY : src/alg/CMakeFiles/alg.dir/build

src/alg/CMakeFiles/alg.dir/requires: src/alg/CMakeFiles/alg.dir/curve_interp.cpp.o.requires
src/alg/CMakeFiles/alg.dir/requires: src/alg/CMakeFiles/alg.dir/Mesh.cpp.o.requires
src/alg/CMakeFiles/alg.dir/requires: src/alg/CMakeFiles/alg.dir/GeodesicGenerator.cpp.o.requires
src/alg/CMakeFiles/alg.dir/requires: src/alg/CMakeFiles/alg.dir/projection.cpp.o.requires
src/alg/CMakeFiles/alg.dir/requires: src/alg/CMakeFiles/alg.dir/CurveGenerator2.cpp.o.requires
src/alg/CMakeFiles/alg.dir/requires: src/alg/CMakeFiles/alg.dir/CurveGenerator.cpp.o.requires
.PHONY : src/alg/CMakeFiles/alg.dir/requires

src/alg/CMakeFiles/alg.dir/clean:
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg && $(CMAKE_COMMAND) -P CMakeFiles/alg.dir/cmake_clean.cmake
.PHONY : src/alg/CMakeFiles/alg.dir/clean

src/alg/CMakeFiles/alg.dir/depend:
	cd /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/src/alg /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg /home/zju/program/svn/KaiyiWang/trunk/framework_cleanup/build-qt5-release/src/alg/CMakeFiles/alg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/alg/CMakeFiles/alg.dir/depend

