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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cole/bin/csci262/project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cole/bin/csci262/project3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.cpp.dir/flags.make

CMakeFiles/main.cpp.dir/hangman.cpp.o: CMakeFiles/main.cpp.dir/flags.make
CMakeFiles/main.cpp.dir/hangman.cpp.o: ../hangman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cole/bin/csci262/project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.cpp.dir/hangman.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.cpp.dir/hangman.cpp.o -c /Users/cole/bin/csci262/project3/hangman.cpp

CMakeFiles/main.cpp.dir/hangman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.cpp.dir/hangman.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cole/bin/csci262/project3/hangman.cpp > CMakeFiles/main.cpp.dir/hangman.cpp.i

CMakeFiles/main.cpp.dir/hangman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.cpp.dir/hangman.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cole/bin/csci262/project3/hangman.cpp -o CMakeFiles/main.cpp.dir/hangman.cpp.s

# Object files for target main.cpp
main_cpp_OBJECTS = \
"CMakeFiles/main.cpp.dir/hangman.cpp.o"

# External object files for target main.cpp
main_cpp_EXTERNAL_OBJECTS =

main.cpp: CMakeFiles/main.cpp.dir/hangman.cpp.o
main.cpp: CMakeFiles/main.cpp.dir/build.make
main.cpp: CMakeFiles/main.cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cole/bin/csci262/project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main.cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.cpp.dir/build: main.cpp

.PHONY : CMakeFiles/main.cpp.dir/build

CMakeFiles/main.cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.cpp.dir/clean

CMakeFiles/main.cpp.dir/depend:
	cd /Users/cole/bin/csci262/project3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cole/bin/csci262/project3 /Users/cole/bin/csci262/project3 /Users/cole/bin/csci262/project3/cmake-build-debug /Users/cole/bin/csci262/project3/cmake-build-debug /Users/cole/bin/csci262/project3/cmake-build-debug/CMakeFiles/main.cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.cpp.dir/depend

