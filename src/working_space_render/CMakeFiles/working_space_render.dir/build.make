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

# Include any dependencies generated for this target.
include src/working_space_render/CMakeFiles/working_space_render.dir/depend.make

# Include the progress variables for this target.
include src/working_space_render/CMakeFiles/working_space_render.dir/progress.make

# Include the compile flags for this target's objects.
include src/working_space_render/CMakeFiles/working_space_render.dir/flags.make

src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o: src/working_space_render/CMakeFiles/working_space_render.dir/flags.make
src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o: src/working_space_render/trimesh_render.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/working_space_render.dir/trimesh_render.cpp.o -c /home/zju/program/github/curve-design/src/working_space_render/trimesh_render.cpp

src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/working_space_render.dir/trimesh_render.cpp.i"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/github/curve-design/src/working_space_render/trimesh_render.cpp > CMakeFiles/working_space_render.dir/trimesh_render.cpp.i

src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/working_space_render.dir/trimesh_render.cpp.s"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/github/curve-design/src/working_space_render/trimesh_render.cpp -o CMakeFiles/working_space_render.dir/trimesh_render.cpp.s

src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.requires:
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.requires

src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.provides: src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.requires
	$(MAKE) -f src/working_space_render/CMakeFiles/working_space_render.dir/build.make src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.provides.build
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.provides

src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.provides.build: src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o

src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o: src/working_space_render/CMakeFiles/working_space_render.dir/flags.make
src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o: src/working_space_render/scene_view.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/working_space_render.dir/scene_view.cpp.o -c /home/zju/program/github/curve-design/src/working_space_render/scene_view.cpp

src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/working_space_render.dir/scene_view.cpp.i"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/github/curve-design/src/working_space_render/scene_view.cpp > CMakeFiles/working_space_render.dir/scene_view.cpp.i

src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/working_space_render.dir/scene_view.cpp.s"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/github/curve-design/src/working_space_render/scene_view.cpp -o CMakeFiles/working_space_render.dir/scene_view.cpp.s

src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.requires:
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.requires

src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.provides: src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.requires
	$(MAKE) -f src/working_space_render/CMakeFiles/working_space_render.dir/build.make src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.provides.build
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.provides

src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.provides.build: src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o

src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o: src/working_space_render/CMakeFiles/working_space_render.dir/flags.make
src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o: src/working_space_render/tri_mesh_render.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o -c /home/zju/program/github/curve-design/src/working_space_render/tri_mesh_render.cpp

src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.i"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/github/curve-design/src/working_space_render/tri_mesh_render.cpp > CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.i

src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.s"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/github/curve-design/src/working_space_render/tri_mesh_render.cpp -o CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.s

src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.requires:
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.requires

src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.provides: src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.requires
	$(MAKE) -f src/working_space_render/CMakeFiles/working_space_render.dir/build.make src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.provides.build
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.provides

src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.provides.build: src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o

src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o: src/working_space_render/CMakeFiles/working_space_render.dir/flags.make
src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o: src/working_space_render/def_ctrl_render.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o -c /home/zju/program/github/curve-design/src/working_space_render/def_ctrl_render.cpp

src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.i"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/github/curve-design/src/working_space_render/def_ctrl_render.cpp > CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.i

src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.s"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/github/curve-design/src/working_space_render/def_ctrl_render.cpp -o CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.s

src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.requires:
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.requires

src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.provides: src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.requires
	$(MAKE) -f src/working_space_render/CMakeFiles/working_space_render.dir/build.make src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.provides.build
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.provides

src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.provides.build: src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o

src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o: src/working_space_render/CMakeFiles/working_space_render.dir/flags.make
src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o: src/working_space_render/sphere_render.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/working_space_render.dir/sphere_render.cpp.o -c /home/zju/program/github/curve-design/src/working_space_render/sphere_render.cpp

src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/working_space_render.dir/sphere_render.cpp.i"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/github/curve-design/src/working_space_render/sphere_render.cpp > CMakeFiles/working_space_render.dir/sphere_render.cpp.i

src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/working_space_render.dir/sphere_render.cpp.s"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/github/curve-design/src/working_space_render/sphere_render.cpp -o CMakeFiles/working_space_render.dir/sphere_render.cpp.s

src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.requires:
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.requires

src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.provides: src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.requires
	$(MAKE) -f src/working_space_render/CMakeFiles/working_space_render.dir/build.make src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.provides.build
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.provides

src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.provides.build: src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o

src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o: src/working_space_render/CMakeFiles/working_space_render.dir/flags.make
src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o: src/working_space_render/line_render.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zju/program/github/curve-design/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/working_space_render.dir/line_render.cpp.o -c /home/zju/program/github/curve-design/src/working_space_render/line_render.cpp

src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/working_space_render.dir/line_render.cpp.i"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zju/program/github/curve-design/src/working_space_render/line_render.cpp > CMakeFiles/working_space_render.dir/line_render.cpp.i

src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/working_space_render.dir/line_render.cpp.s"
	cd /home/zju/program/github/curve-design/src/working_space_render && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zju/program/github/curve-design/src/working_space_render/line_render.cpp -o CMakeFiles/working_space_render.dir/line_render.cpp.s

src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.requires:
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.requires

src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.provides: src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.requires
	$(MAKE) -f src/working_space_render/CMakeFiles/working_space_render.dir/build.make src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.provides.build
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.provides

src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.provides.build: src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o

# Object files for target working_space_render
working_space_render_OBJECTS = \
"CMakeFiles/working_space_render.dir/trimesh_render.cpp.o" \
"CMakeFiles/working_space_render.dir/scene_view.cpp.o" \
"CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o" \
"CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o" \
"CMakeFiles/working_space_render.dir/sphere_render.cpp.o" \
"CMakeFiles/working_space_render.dir/line_render.cpp.o"

# External object files for target working_space_render
working_space_render_EXTERNAL_OBJECTS =

lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/build.make
lib/libworking_space_render.so: lib/libglobals.so
lib/libworking_space_render.so: /usr/lib/libosg.so
lib/libworking_space_render.so: /usr/lib/libosgUtil.so
lib/libworking_space_render.so: /usr/lib/libosgDB.so
lib/libworking_space_render.so: /usr/lib/libosgText.so
lib/libworking_space_render.so: /usr/lib/libosgViewer.so
lib/libworking_space_render.so: /usr/lib/libosgGA.so
lib/libworking_space_render.so: /usr/lib/libosgManipulator.so
lib/libworking_space_render.so: /usr/lib/libosgFX.so
lib/libworking_space_render.so: /usr/lib/libOpenThreads.so
lib/libworking_space_render.so: /usr/lib/x86_64-linux-gnu/libglut.so
lib/libworking_space_render.so: /usr/lib/x86_64-linux-gnu/libXmu.so
lib/libworking_space_render.so: /usr/lib/x86_64-linux-gnu/libXi.so
lib/libworking_space_render.so: src/working_space_render/CMakeFiles/working_space_render.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../lib/libworking_space_render.so"
	cd /home/zju/program/github/curve-design/src/working_space_render && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/working_space_render.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/working_space_render/CMakeFiles/working_space_render.dir/build: lib/libworking_space_render.so
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/build

src/working_space_render/CMakeFiles/working_space_render.dir/requires: src/working_space_render/CMakeFiles/working_space_render.dir/trimesh_render.cpp.o.requires
src/working_space_render/CMakeFiles/working_space_render.dir/requires: src/working_space_render/CMakeFiles/working_space_render.dir/scene_view.cpp.o.requires
src/working_space_render/CMakeFiles/working_space_render.dir/requires: src/working_space_render/CMakeFiles/working_space_render.dir/tri_mesh_render.cpp.o.requires
src/working_space_render/CMakeFiles/working_space_render.dir/requires: src/working_space_render/CMakeFiles/working_space_render.dir/def_ctrl_render.cpp.o.requires
src/working_space_render/CMakeFiles/working_space_render.dir/requires: src/working_space_render/CMakeFiles/working_space_render.dir/sphere_render.cpp.o.requires
src/working_space_render/CMakeFiles/working_space_render.dir/requires: src/working_space_render/CMakeFiles/working_space_render.dir/line_render.cpp.o.requires
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/requires

src/working_space_render/CMakeFiles/working_space_render.dir/clean:
	cd /home/zju/program/github/curve-design/src/working_space_render && $(CMAKE_COMMAND) -P CMakeFiles/working_space_render.dir/cmake_clean.cmake
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/clean

src/working_space_render/CMakeFiles/working_space_render.dir/depend:
	cd /home/zju/program/github/curve-design && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zju/program/github/curve-design /home/zju/program/github/curve-design/src/working_space_render /home/zju/program/github/curve-design /home/zju/program/github/curve-design/src/working_space_render /home/zju/program/github/curve-design/src/working_space_render/CMakeFiles/working_space_render.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/working_space_render/CMakeFiles/working_space_render.dir/depend

