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
CMAKE_SOURCE_DIR = /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries

# Include any dependencies generated for this target.
include CMakeFiles/lab5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab5.dir/flags.make

CMakeFiles/lab5.dir/main.cpp.o: CMakeFiles/lab5.dir/flags.make
CMakeFiles/lab5.dir/main.cpp.o: /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab5.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab5.dir/main.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/main.cpp

CMakeFiles/lab5.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab5.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/main.cpp > CMakeFiles/lab5.dir/main.cpp.i

CMakeFiles/lab5.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab5.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/main.cpp -o CMakeFiles/lab5.dir/main.cpp.s

CMakeFiles/lab5.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/lab5.dir/main.cpp.o.requires

CMakeFiles/lab5.dir/main.cpp.o.provides: CMakeFiles/lab5.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab5.dir/build.make CMakeFiles/lab5.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/lab5.dir/main.cpp.o.provides

CMakeFiles/lab5.dir/main.cpp.o.provides.build: CMakeFiles/lab5.dir/main.cpp.o

CMakeFiles/lab5.dir/GLSL.cpp.o: CMakeFiles/lab5.dir/flags.make
CMakeFiles/lab5.dir/GLSL.cpp.o: /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/GLSL.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab5.dir/GLSL.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab5.dir/GLSL.cpp.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/GLSL.cpp

CMakeFiles/lab5.dir/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab5.dir/GLSL.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/GLSL.cpp > CMakeFiles/lab5.dir/GLSL.cpp.i

CMakeFiles/lab5.dir/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab5.dir/GLSL.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/GLSL.cpp -o CMakeFiles/lab5.dir/GLSL.cpp.s

CMakeFiles/lab5.dir/GLSL.cpp.o.requires:
.PHONY : CMakeFiles/lab5.dir/GLSL.cpp.o.requires

CMakeFiles/lab5.dir/GLSL.cpp.o.provides: CMakeFiles/lab5.dir/GLSL.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab5.dir/build.make CMakeFiles/lab5.dir/GLSL.cpp.o.provides.build
.PHONY : CMakeFiles/lab5.dir/GLSL.cpp.o.provides

CMakeFiles/lab5.dir/GLSL.cpp.o.provides.build: CMakeFiles/lab5.dir/GLSL.cpp.o

CMakeFiles/lab5.dir/tiny_obj_loader.cc.o: CMakeFiles/lab5.dir/flags.make
CMakeFiles/lab5.dir/tiny_obj_loader.cc.o: /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/tiny_obj_loader.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lab5.dir/tiny_obj_loader.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lab5.dir/tiny_obj_loader.cc.o -c /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/tiny_obj_loader.cc

CMakeFiles/lab5.dir/tiny_obj_loader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab5.dir/tiny_obj_loader.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/tiny_obj_loader.cc > CMakeFiles/lab5.dir/tiny_obj_loader.cc.i

CMakeFiles/lab5.dir/tiny_obj_loader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab5.dir/tiny_obj_loader.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release/tiny_obj_loader.cc -o CMakeFiles/lab5.dir/tiny_obj_loader.cc.s

CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.requires:
.PHONY : CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.requires

CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.provides: CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.requires
	$(MAKE) -f CMakeFiles/lab5.dir/build.make CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.provides.build
.PHONY : CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.provides

CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.provides.build: CMakeFiles/lab5.dir/tiny_obj_loader.cc.o

# Object files for target lab5
lab5_OBJECTS = \
"CMakeFiles/lab5.dir/main.cpp.o" \
"CMakeFiles/lab5.dir/GLSL.cpp.o" \
"CMakeFiles/lab5.dir/tiny_obj_loader.cc.o"

# External object files for target lab5
lab5_EXTERNAL_OBJECTS =

lab5: CMakeFiles/lab5.dir/main.cpp.o
lab5: CMakeFiles/lab5.dir/GLSL.cpp.o
lab5: CMakeFiles/lab5.dir/tiny_obj_loader.cc.o
lab5: CMakeFiles/lab5.dir/build.make
lab5: /usr/local/lib/libglfw3.dylib
lab5: /opt/local/lib/libGLEW.dylib
lab5: CMakeFiles/lab5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lab5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab5.dir/build: lab5
.PHONY : CMakeFiles/lab5.dir/build

CMakeFiles/lab5.dir/requires: CMakeFiles/lab5.dir/main.cpp.o.requires
CMakeFiles/lab5.dir/requires: CMakeFiles/lab5.dir/GLSL.cpp.o.requires
CMakeFiles/lab5.dir/requires: CMakeFiles/lab5.dir/tiny_obj_loader.cc.o.requires
.PHONY : CMakeFiles/lab5.dir/requires

CMakeFiles/lab5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab5.dir/clean

CMakeFiles/lab5.dir/depend:
	cd /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Lab5_15_release /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries /Users/Ian/Documents/Cal-Poly/cpe471/lab5/Binaries/CMakeFiles/lab5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab5.dir/depend
