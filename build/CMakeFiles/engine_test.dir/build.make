# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/evan/Projects/GameEnginev2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/evan/Projects/GameEnginev2/build

# Include any dependencies generated for this target.
include CMakeFiles/engine_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/engine_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/engine_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine_test.dir/flags.make

CMakeFiles/engine_test.dir/src/test.c.o: CMakeFiles/engine_test.dir/flags.make
CMakeFiles/engine_test.dir/src/test.c.o: ../src/test.c
CMakeFiles/engine_test.dir/src/test.c.o: CMakeFiles/engine_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/evan/Projects/GameEnginev2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/engine_test.dir/src/test.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/engine_test.dir/src/test.c.o -MF CMakeFiles/engine_test.dir/src/test.c.o.d -o CMakeFiles/engine_test.dir/src/test.c.o -c /Users/evan/Projects/GameEnginev2/src/test.c

CMakeFiles/engine_test.dir/src/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/engine_test.dir/src/test.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/evan/Projects/GameEnginev2/src/test.c > CMakeFiles/engine_test.dir/src/test.c.i

CMakeFiles/engine_test.dir/src/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/engine_test.dir/src/test.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/evan/Projects/GameEnginev2/src/test.c -o CMakeFiles/engine_test.dir/src/test.c.s

# Object files for target engine_test
engine_test_OBJECTS = \
"CMakeFiles/engine_test.dir/src/test.c.o"

# External object files for target engine_test
engine_test_EXTERNAL_OBJECTS =

engine_test: CMakeFiles/engine_test.dir/src/test.c.o
engine_test: CMakeFiles/engine_test.dir/build.make
engine_test: libengine.a
engine_test: deps/glfw/src/libglfw3.a
engine_test: deps/glad/libglad.a
engine_test: deps/stb/libstb.a
engine_test: CMakeFiles/engine_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/evan/Projects/GameEnginev2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable engine_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine_test.dir/build: engine_test
.PHONY : CMakeFiles/engine_test.dir/build

CMakeFiles/engine_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine_test.dir/clean

CMakeFiles/engine_test.dir/depend:
	cd /Users/evan/Projects/GameEnginev2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/evan/Projects/GameEnginev2 /Users/evan/Projects/GameEnginev2 /Users/evan/Projects/GameEnginev2/build /Users/evan/Projects/GameEnginev2/build /Users/evan/Projects/GameEnginev2/build/CMakeFiles/engine_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/engine_test.dir/depend

