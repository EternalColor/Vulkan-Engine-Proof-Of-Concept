# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = /home/sascha/HDD1/VulkanTest2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sascha/HDD1/VulkanTest2

# Utility rule file for some_target.

# Include the progress variables for this target.
include shaders/CMakeFiles/some_target.dir/progress.make

shaders/CMakeFiles/some_target: /usr/share/cmake-3.19/build/*.spv


/usr/share/cmake-3.19/build/*.spv:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/sascha/HDD1/VulkanTest2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Compiling shaders..."
	cd /home/sascha/HDD1/VulkanTest2/shaders && glslangValidator -V *.vert && glslangValidator -V *.frag

some_target: shaders/CMakeFiles/some_target
some_target: /usr/share/cmake-3.19/build/*.spv
some_target: shaders/CMakeFiles/some_target.dir/build.make

.PHONY : some_target

# Rule to build all files generated by this target.
shaders/CMakeFiles/some_target.dir/build: some_target

.PHONY : shaders/CMakeFiles/some_target.dir/build

shaders/CMakeFiles/some_target.dir/clean:
	cd /home/sascha/HDD1/VulkanTest2/shaders && $(CMAKE_COMMAND) -P CMakeFiles/some_target.dir/cmake_clean.cmake
.PHONY : shaders/CMakeFiles/some_target.dir/clean

shaders/CMakeFiles/some_target.dir/depend:
	cd /home/sascha/HDD1/VulkanTest2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sascha/HDD1/VulkanTest2 /home/sascha/HDD1/VulkanTest2/shaders /home/sascha/HDD1/VulkanTest2 /home/sascha/HDD1/VulkanTest2/shaders /home/sascha/HDD1/VulkanTest2/shaders/CMakeFiles/some_target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : shaders/CMakeFiles/some_target.dir/depend
