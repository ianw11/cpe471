# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Ian/Documents/Cal-Poly/cpe471/lab6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Ian/Documents/Cal-Poly/cpe471/lab6

# Include any dependencies generated for this target.
include CMakeFiles/Lab6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab6.dir/flags.make

CMakeFiles/Lab6.dir/source/main.cpp.o: CMakeFiles/Lab6.dir/flags.make
CMakeFiles/Lab6.dir/source/main.cpp.o: source/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab6/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Lab6.dir/source/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Lab6.dir/source/main.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/main.cpp

CMakeFiles/Lab6.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab6.dir/source/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/main.cpp > CMakeFiles/Lab6.dir/source/main.cpp.i

CMakeFiles/Lab6.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab6.dir/source/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/main.cpp -o CMakeFiles/Lab6.dir/source/main.cpp.s

CMakeFiles/Lab6.dir/source/main.cpp.o.requires:
.PHONY : CMakeFiles/Lab6.dir/source/main.cpp.o.requires

CMakeFiles/Lab6.dir/source/main.cpp.o.provides: CMakeFiles/Lab6.dir/source/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab6.dir/build.make CMakeFiles/Lab6.dir/source/main.cpp.o.provides.build
.PHONY : CMakeFiles/Lab6.dir/source/main.cpp.o.provides

CMakeFiles/Lab6.dir/source/main.cpp.o.provides.build: CMakeFiles/Lab6.dir/source/main.cpp.o

CMakeFiles/Lab6.dir/source/GLSL.cpp.o: CMakeFiles/Lab6.dir/flags.make
CMakeFiles/Lab6.dir/source/GLSL.cpp.o: source/GLSL.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab6/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Lab6.dir/source/GLSL.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Lab6.dir/source/GLSL.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/GLSL.cpp

CMakeFiles/Lab6.dir/source/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab6.dir/source/GLSL.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/GLSL.cpp > CMakeFiles/Lab6.dir/source/GLSL.cpp.i

CMakeFiles/Lab6.dir/source/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab6.dir/source/GLSL.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/GLSL.cpp -o CMakeFiles/Lab6.dir/source/GLSL.cpp.s

CMakeFiles/Lab6.dir/source/GLSL.cpp.o.requires:
.PHONY : CMakeFiles/Lab6.dir/source/GLSL.cpp.o.requires

CMakeFiles/Lab6.dir/source/GLSL.cpp.o.provides: CMakeFiles/Lab6.dir/source/GLSL.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab6.dir/build.make CMakeFiles/Lab6.dir/source/GLSL.cpp.o.provides.build
.PHONY : CMakeFiles/Lab6.dir/source/GLSL.cpp.o.provides

CMakeFiles/Lab6.dir/source/GLSL.cpp.o.provides.build: CMakeFiles/Lab6.dir/source/GLSL.cpp.o

CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o: CMakeFiles/Lab6.dir/flags.make
CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o: source/tiny_obj_loader.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab6/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/tiny_obj_loader.cc

CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/tiny_obj_loader.cc > CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.i

CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/tiny_obj_loader.cc -o CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.s

CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.requires:
.PHONY : CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.requires

CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.provides: CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.requires
	$(MAKE) -f CMakeFiles/Lab6.dir/build.make CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.provides.build
.PHONY : CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.provides

CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.provides.build: CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o

CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o: CMakeFiles/Lab6.dir/flags.make
CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o: source/RenderingHelper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab6/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/RenderingHelper.cpp

CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/RenderingHelper.cpp > CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.i

CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab6/source/RenderingHelper.cpp -o CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.s

CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.requires:
.PHONY : CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.requires

CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.provides: CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.requires
	$(MAKE) -f CMakeFiles/Lab6.dir/build.make CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.provides.build
.PHONY : CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.provides

CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.provides.build: CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o

CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o: CMakeFiles/Lab6.dir/flags.make
CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o: dependencies/glad/src/glad.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab6/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o   -c /Users/Ian/Documents/Cal-Poly/cpe471/lab6/dependencies/glad/src/glad.c

CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab6/dependencies/glad/src/glad.c > CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.i

CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab6/dependencies/glad/src/glad.c -o CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.s

CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.requires:
.PHONY : CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.requires

CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.provides: CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.requires
	$(MAKE) -f CMakeFiles/Lab6.dir/build.make CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.provides.build
.PHONY : CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.provides

CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.provides.build: CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o

# Object files for target Lab6
Lab6_OBJECTS = \
"CMakeFiles/Lab6.dir/source/main.cpp.o" \
"CMakeFiles/Lab6.dir/source/GLSL.cpp.o" \
"CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o" \
"CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o" \
"CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o"

# External object files for target Lab6
Lab6_EXTERNAL_OBJECTS =

Lab6: CMakeFiles/Lab6.dir/source/main.cpp.o
Lab6: CMakeFiles/Lab6.dir/source/GLSL.cpp.o
Lab6: CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o
Lab6: CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o
Lab6: CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o
Lab6: CMakeFiles/Lab6.dir/build.make
Lab6: dependencies/glfw/src/libglfw3.a
Lab6: CMakeFiles/Lab6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Lab6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab6.dir/build: Lab6
.PHONY : CMakeFiles/Lab6.dir/build

CMakeFiles/Lab6.dir/requires: CMakeFiles/Lab6.dir/source/main.cpp.o.requires
CMakeFiles/Lab6.dir/requires: CMakeFiles/Lab6.dir/source/GLSL.cpp.o.requires
CMakeFiles/Lab6.dir/requires: CMakeFiles/Lab6.dir/source/tiny_obj_loader.cc.o.requires
CMakeFiles/Lab6.dir/requires: CMakeFiles/Lab6.dir/source/RenderingHelper.cpp.o.requires
CMakeFiles/Lab6.dir/requires: CMakeFiles/Lab6.dir/dependencies/glad/src/glad.c.o.requires
.PHONY : CMakeFiles/Lab6.dir/requires

CMakeFiles/Lab6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab6.dir/clean

CMakeFiles/Lab6.dir/depend:
	cd /Users/Ian/Documents/Cal-Poly/cpe471/lab6 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Ian/Documents/Cal-Poly/cpe471/lab6 /Users/Ian/Documents/Cal-Poly/cpe471/lab6 /Users/Ian/Documents/Cal-Poly/cpe471/lab6 /Users/Ian/Documents/Cal-Poly/cpe471/lab6 /Users/Ian/Documents/Cal-Poly/cpe471/lab6/CMakeFiles/Lab6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab6.dir/depend

