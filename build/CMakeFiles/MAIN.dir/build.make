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
CMAKE_SOURCE_DIR = /home/conner/coding/wildfire

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/conner/coding/wildfire/build

# Include any dependencies generated for this target.
include CMakeFiles/MAIN.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MAIN.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MAIN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MAIN.dir/flags.make

CMakeFiles/MAIN.dir/main.cpp.o: CMakeFiles/MAIN.dir/flags.make
CMakeFiles/MAIN.dir/main.cpp.o: ../main.cpp
CMakeFiles/MAIN.dir/main.cpp.o: CMakeFiles/MAIN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/conner/coding/wildfire/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MAIN.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MAIN.dir/main.cpp.o -MF CMakeFiles/MAIN.dir/main.cpp.o.d -o CMakeFiles/MAIN.dir/main.cpp.o -c /home/conner/coding/wildfire/main.cpp

CMakeFiles/MAIN.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MAIN.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/conner/coding/wildfire/main.cpp > CMakeFiles/MAIN.dir/main.cpp.i

CMakeFiles/MAIN.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MAIN.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/conner/coding/wildfire/main.cpp -o CMakeFiles/MAIN.dir/main.cpp.s

CMakeFiles/MAIN.dir/RenderEngine.cpp.o: CMakeFiles/MAIN.dir/flags.make
CMakeFiles/MAIN.dir/RenderEngine.cpp.o: ../RenderEngine.cpp
CMakeFiles/MAIN.dir/RenderEngine.cpp.o: CMakeFiles/MAIN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/conner/coding/wildfire/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MAIN.dir/RenderEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MAIN.dir/RenderEngine.cpp.o -MF CMakeFiles/MAIN.dir/RenderEngine.cpp.o.d -o CMakeFiles/MAIN.dir/RenderEngine.cpp.o -c /home/conner/coding/wildfire/RenderEngine.cpp

CMakeFiles/MAIN.dir/RenderEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MAIN.dir/RenderEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/conner/coding/wildfire/RenderEngine.cpp > CMakeFiles/MAIN.dir/RenderEngine.cpp.i

CMakeFiles/MAIN.dir/RenderEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MAIN.dir/RenderEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/conner/coding/wildfire/RenderEngine.cpp -o CMakeFiles/MAIN.dir/RenderEngine.cpp.s

CMakeFiles/MAIN.dir/game.cpp.o: CMakeFiles/MAIN.dir/flags.make
CMakeFiles/MAIN.dir/game.cpp.o: ../game.cpp
CMakeFiles/MAIN.dir/game.cpp.o: CMakeFiles/MAIN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/conner/coding/wildfire/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MAIN.dir/game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MAIN.dir/game.cpp.o -MF CMakeFiles/MAIN.dir/game.cpp.o.d -o CMakeFiles/MAIN.dir/game.cpp.o -c /home/conner/coding/wildfire/game.cpp

CMakeFiles/MAIN.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MAIN.dir/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/conner/coding/wildfire/game.cpp > CMakeFiles/MAIN.dir/game.cpp.i

CMakeFiles/MAIN.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MAIN.dir/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/conner/coding/wildfire/game.cpp -o CMakeFiles/MAIN.dir/game.cpp.s

CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o: CMakeFiles/MAIN.dir/flags.make
CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o: ../lib/Vec2f.cpp
CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o: CMakeFiles/MAIN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/conner/coding/wildfire/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o -MF CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o.d -o CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o -c /home/conner/coding/wildfire/lib/Vec2f.cpp

CMakeFiles/MAIN.dir/lib/Vec2f.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MAIN.dir/lib/Vec2f.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/conner/coding/wildfire/lib/Vec2f.cpp > CMakeFiles/MAIN.dir/lib/Vec2f.cpp.i

CMakeFiles/MAIN.dir/lib/Vec2f.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MAIN.dir/lib/Vec2f.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/conner/coding/wildfire/lib/Vec2f.cpp -o CMakeFiles/MAIN.dir/lib/Vec2f.cpp.s

CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o: CMakeFiles/MAIN.dir/flags.make
CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o: ../lib/Vec2i.cpp
CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o: CMakeFiles/MAIN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/conner/coding/wildfire/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o -MF CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o.d -o CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o -c /home/conner/coding/wildfire/lib/Vec2i.cpp

CMakeFiles/MAIN.dir/lib/Vec2i.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MAIN.dir/lib/Vec2i.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/conner/coding/wildfire/lib/Vec2i.cpp > CMakeFiles/MAIN.dir/lib/Vec2i.cpp.i

CMakeFiles/MAIN.dir/lib/Vec2i.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MAIN.dir/lib/Vec2i.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/conner/coding/wildfire/lib/Vec2i.cpp -o CMakeFiles/MAIN.dir/lib/Vec2i.cpp.s

# Object files for target MAIN
MAIN_OBJECTS = \
"CMakeFiles/MAIN.dir/main.cpp.o" \
"CMakeFiles/MAIN.dir/RenderEngine.cpp.o" \
"CMakeFiles/MAIN.dir/game.cpp.o" \
"CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o" \
"CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o"

# External object files for target MAIN
MAIN_EXTERNAL_OBJECTS =

MAIN: CMakeFiles/MAIN.dir/main.cpp.o
MAIN: CMakeFiles/MAIN.dir/RenderEngine.cpp.o
MAIN: CMakeFiles/MAIN.dir/game.cpp.o
MAIN: CMakeFiles/MAIN.dir/lib/Vec2f.cpp.o
MAIN: CMakeFiles/MAIN.dir/lib/Vec2i.cpp.o
MAIN: CMakeFiles/MAIN.dir/build.make
MAIN: CMakeFiles/MAIN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/conner/coding/wildfire/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable MAIN"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MAIN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MAIN.dir/build: MAIN
.PHONY : CMakeFiles/MAIN.dir/build

CMakeFiles/MAIN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MAIN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MAIN.dir/clean

CMakeFiles/MAIN.dir/depend:
	cd /home/conner/coding/wildfire/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/conner/coding/wildfire /home/conner/coding/wildfire /home/conner/coding/wildfire/build /home/conner/coding/wildfire/build /home/conner/coding/wildfire/build/CMakeFiles/MAIN.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MAIN.dir/depend
