# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/xixi2-software/CLion-2019.1.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/xixi2-software/CLion-2019.1.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/0708_vector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/0708_vector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/0708_vector.dir/flags.make

CMakeFiles/0708_vector.dir/main.cpp.o: CMakeFiles/0708_vector.dir/flags.make
CMakeFiles/0708_vector.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/0708_vector.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/0708_vector.dir/main.cpp.o -c /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/main.cpp

CMakeFiles/0708_vector.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0708_vector.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/main.cpp > CMakeFiles/0708_vector.dir/main.cpp.i

CMakeFiles/0708_vector.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0708_vector.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/main.cpp -o CMakeFiles/0708_vector.dir/main.cpp.s

# Object files for target 0708_vector
0708_vector_OBJECTS = \
"CMakeFiles/0708_vector.dir/main.cpp.o"

# External object files for target 0708_vector
0708_vector_EXTERNAL_OBJECTS =

0708_vector: CMakeFiles/0708_vector.dir/main.cpp.o
0708_vector: CMakeFiles/0708_vector.dir/build.make
0708_vector: CMakeFiles/0708_vector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 0708_vector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/0708_vector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/0708_vector.dir/build: 0708_vector

.PHONY : CMakeFiles/0708_vector.dir/build

CMakeFiles/0708_vector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/0708_vector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/0708_vector.dir/clean

CMakeFiles/0708_vector.dir/depend:
	cd /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug /home/xixi2/文档/CLionProjects/c_algorithm/algorithms/VectorImple/cmake-build-debug/CMakeFiles/0708_vector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/0708_vector.dir/depend

