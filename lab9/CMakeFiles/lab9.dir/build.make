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
CMAKE_SOURCE_DIR = /Users/Ian/Documents/Cal-Poly/cpe471/lab9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Ian/Documents/Cal-Poly/cpe471/lab9

# Include any dependencies generated for this target.
include CMakeFiles/lab9.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab9.dir/flags.make

CMakeFiles/lab9.dir/main.cpp.o: CMakeFiles/lab9.dir/flags.make
CMakeFiles/lab9.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab9/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab9.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab9.dir/main.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab9/main.cpp

CMakeFiles/lab9.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab9.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab9/main.cpp > CMakeFiles/lab9.dir/main.cpp.i

CMakeFiles/lab9.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab9.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab9/main.cpp -o CMakeFiles/lab9.dir/main.cpp.s

CMakeFiles/lab9.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/lab9.dir/main.cpp.o.requires

CMakeFiles/lab9.dir/main.cpp.o.provides: CMakeFiles/lab9.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab9.dir/build.make CMakeFiles/lab9.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/lab9.dir/main.cpp.o.provides

CMakeFiles/lab9.dir/main.cpp.o.provides.build: CMakeFiles/lab9.dir/main.cpp.o

CMakeFiles/lab9.dir/GLSL.cpp.o: CMakeFiles/lab9.dir/flags.make
CMakeFiles/lab9.dir/GLSL.cpp.o: GLSL.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab9/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab9.dir/GLSL.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab9.dir/GLSL.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab9/GLSL.cpp

CMakeFiles/lab9.dir/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab9.dir/GLSL.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab9/GLSL.cpp > CMakeFiles/lab9.dir/GLSL.cpp.i

CMakeFiles/lab9.dir/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab9.dir/GLSL.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab9/GLSL.cpp -o CMakeFiles/lab9.dir/GLSL.cpp.s

CMakeFiles/lab9.dir/GLSL.cpp.o.requires:
.PHONY : CMakeFiles/lab9.dir/GLSL.cpp.o.requires

CMakeFiles/lab9.dir/GLSL.cpp.o.provides: CMakeFiles/lab9.dir/GLSL.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab9.dir/build.make CMakeFiles/lab9.dir/GLSL.cpp.o.provides.build
.PHONY : CMakeFiles/lab9.dir/GLSL.cpp.o.provides

CMakeFiles/lab9.dir/GLSL.cpp.o.provides.build: CMakeFiles/lab9.dir/GLSL.cpp.o

CMakeFiles/lab9.dir/tiny_obj_loader.cc.o: CMakeFiles/lab9.dir/flags.make
CMakeFiles/lab9.dir/tiny_obj_loader.cc.o: tiny_obj_loader.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab9/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab9.dir/tiny_obj_loader.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab9.dir/tiny_obj_loader.cc.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab9/tiny_obj_loader.cc

CMakeFiles/lab9.dir/tiny_obj_loader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab9.dir/tiny_obj_loader.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab9/tiny_obj_loader.cc > CMakeFiles/lab9.dir/tiny_obj_loader.cc.i

CMakeFiles/lab9.dir/tiny_obj_loader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab9.dir/tiny_obj_loader.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab9/tiny_obj_loader.cc -o CMakeFiles/lab9.dir/tiny_obj_loader.cc.s

CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.requires:
.PHONY : CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.requires

CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.provides: CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.requires
	$(MAKE) -f CMakeFiles/lab9.dir/build.make CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.provides.build
.PHONY : CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.provides

CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.provides.build: CMakeFiles/lab9.dir/tiny_obj_loader.cc.o

CMakeFiles/lab9.dir/RenderingHelper.cpp.o: CMakeFiles/lab9.dir/flags.make
CMakeFiles/lab9.dir/RenderingHelper.cpp.o: RenderingHelper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab9/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab9.dir/RenderingHelper.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab9.dir/RenderingHelper.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab9/RenderingHelper.cpp

CMakeFiles/lab9.dir/RenderingHelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab9.dir/RenderingHelper.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab9/RenderingHelper.cpp > CMakeFiles/lab9.dir/RenderingHelper.cpp.i

CMakeFiles/lab9.dir/RenderingHelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab9.dir/RenderingHelper.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab9/RenderingHelper.cpp -o CMakeFiles/lab9.dir/RenderingHelper.cpp.s

CMakeFiles/lab9.dir/RenderingHelper.cpp.o.requires:
.PHONY : CMakeFiles/lab9.dir/RenderingHelper.cpp.o.requires

CMakeFiles/lab9.dir/RenderingHelper.cpp.o.provides: CMakeFiles/lab9.dir/RenderingHelper.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab9.dir/build.make CMakeFiles/lab9.dir/RenderingHelper.cpp.o.provides.build
.PHONY : CMakeFiles/lab9.dir/RenderingHelper.cpp.o.provides

CMakeFiles/lab9.dir/RenderingHelper.cpp.o.provides.build: CMakeFiles/lab9.dir/RenderingHelper.cpp.o

# Object files for target lab9
lab9_OBJECTS = \
"CMakeFiles/lab9.dir/main.cpp.o" \
"CMakeFiles/lab9.dir/GLSL.cpp.o" \
"CMakeFiles/lab9.dir/tiny_obj_loader.cc.o" \
"CMakeFiles/lab9.dir/RenderingHelper.cpp.o"

# External object files for target lab9
lab9_EXTERNAL_OBJECTS =

lab9: CMakeFiles/lab9.dir/main.cpp.o
lab9: CMakeFiles/lab9.dir/GLSL.cpp.o
lab9: CMakeFiles/lab9.dir/tiny_obj_loader.cc.o
lab9: CMakeFiles/lab9.dir/RenderingHelper.cpp.o
lab9: CMakeFiles/lab9.dir/build.make
lab9: /usr/local/lib/libGLEW.dylib
lab9: /usr/local/lib/libglfw3.dylib
lab9: /usr/local/lib/libGLEW.dylib
lab9: /usr/local/lib/libglfw3.dylib
lab9: CMakeFiles/lab9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lab9"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab9.dir/build: lab9
.PHONY : CMakeFiles/lab9.dir/build

CMakeFiles/lab9.dir/requires: CMakeFiles/lab9.dir/main.cpp.o.requires
CMakeFiles/lab9.dir/requires: CMakeFiles/lab9.dir/GLSL.cpp.o.requires
CMakeFiles/lab9.dir/requires: CMakeFiles/lab9.dir/tiny_obj_loader.cc.o.requires
CMakeFiles/lab9.dir/requires: CMakeFiles/lab9.dir/RenderingHelper.cpp.o.requires
.PHONY : CMakeFiles/lab9.dir/requires

CMakeFiles/lab9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab9.dir/clean

CMakeFiles/lab9.dir/depend:
	cd /Users/Ian/Documents/Cal-Poly/cpe471/lab9 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Ian/Documents/Cal-Poly/cpe471/lab9 /Users/Ian/Documents/Cal-Poly/cpe471/lab9 /Users/Ian/Documents/Cal-Poly/cpe471/lab9 /Users/Ian/Documents/Cal-Poly/cpe471/lab9 /Users/Ian/Documents/Cal-Poly/cpe471/lab9/CMakeFiles/lab9.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab9.dir/depend

