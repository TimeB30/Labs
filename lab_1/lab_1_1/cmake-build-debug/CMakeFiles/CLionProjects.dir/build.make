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
CMAKE_SOURCE_DIR = /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CLionProjects.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CLionProjects.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CLionProjects.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CLionProjects.dir/flags.make

CMakeFiles/CLionProjects.dir/main.c.o: CMakeFiles/CLionProjects.dir/flags.make
CMakeFiles/CLionProjects.dir/main.c.o: ../main.c
CMakeFiles/CLionProjects.dir/main.c.o: CMakeFiles/CLionProjects.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CLionProjects.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLionProjects.dir/main.c.o -MF CMakeFiles/CLionProjects.dir/main.c.o.d -o CMakeFiles/CLionProjects.dir/main.c.o -c /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/main.c

CMakeFiles/CLionProjects.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/CLionProjects.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/main.c > CMakeFiles/CLionProjects.dir/main.c.i

CMakeFiles/CLionProjects.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/CLionProjects.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/main.c -o CMakeFiles/CLionProjects.dir/main.c.s

# Object files for target CLionProjects
CLionProjects_OBJECTS = \
"CMakeFiles/CLionProjects.dir/main.c.o"

# External object files for target CLionProjects
CLionProjects_EXTERNAL_OBJECTS =

CLionProjects: CMakeFiles/CLionProjects.dir/main.c.o
CLionProjects: CMakeFiles/CLionProjects.dir/build.make
CLionProjects: libfunc.so
CLionProjects: CMakeFiles/CLionProjects.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable CLionProjects"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CLionProjects.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CLionProjects.dir/build: CLionProjects
.PHONY : CMakeFiles/CLionProjects.dir/build

CMakeFiles/CLionProjects.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CLionProjects.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CLionProjects.dir/clean

CMakeFiles/CLionProjects.dir/depend:
	cd /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1 /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1 /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug /home/timeb/Desktop/mat_prac_labs/lab_1/lab_1_1/cmake-build-debug/CMakeFiles/CLionProjects.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CLionProjects.dir/depend

