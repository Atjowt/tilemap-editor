# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/atjowt/dev/tilemap-editor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/atjowt/dev/tilemap-editor/build

# Include any dependencies generated for this target.
include CMakeFiles/tilemap-editor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tilemap-editor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tilemap-editor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tilemap-editor.dir/flags.make

CMakeFiles/tilemap-editor.dir/main.c.o: CMakeFiles/tilemap-editor.dir/flags.make
CMakeFiles/tilemap-editor.dir/main.c.o: ../main.c
CMakeFiles/tilemap-editor.dir/main.c.o: CMakeFiles/tilemap-editor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/atjowt/dev/tilemap-editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tilemap-editor.dir/main.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tilemap-editor.dir/main.c.o -MF CMakeFiles/tilemap-editor.dir/main.c.o.d -o CMakeFiles/tilemap-editor.dir/main.c.o -c /home/atjowt/dev/tilemap-editor/main.c

CMakeFiles/tilemap-editor.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tilemap-editor.dir/main.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/atjowt/dev/tilemap-editor/main.c > CMakeFiles/tilemap-editor.dir/main.c.i

CMakeFiles/tilemap-editor.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tilemap-editor.dir/main.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/atjowt/dev/tilemap-editor/main.c -o CMakeFiles/tilemap-editor.dir/main.c.s

# Object files for target tilemap-editor
tilemap__editor_OBJECTS = \
"CMakeFiles/tilemap-editor.dir/main.c.o"

# External object files for target tilemap-editor
tilemap__editor_EXTERNAL_OBJECTS =

tilemap-editor: CMakeFiles/tilemap-editor.dir/main.c.o
tilemap-editor: CMakeFiles/tilemap-editor.dir/build.make
tilemap-editor: CMakeFiles/tilemap-editor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/atjowt/dev/tilemap-editor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable tilemap-editor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tilemap-editor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tilemap-editor.dir/build: tilemap-editor
.PHONY : CMakeFiles/tilemap-editor.dir/build

CMakeFiles/tilemap-editor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tilemap-editor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tilemap-editor.dir/clean

CMakeFiles/tilemap-editor.dir/depend:
	cd /home/atjowt/dev/tilemap-editor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/atjowt/dev/tilemap-editor /home/atjowt/dev/tilemap-editor /home/atjowt/dev/tilemap-editor/build /home/atjowt/dev/tilemap-editor/build /home/atjowt/dev/tilemap-editor/build/CMakeFiles/tilemap-editor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tilemap-editor.dir/depend

