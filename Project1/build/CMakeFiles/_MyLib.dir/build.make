# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zwimer/School/OpSys/Project1/Project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zwimer/School/OpSys/Project1/Project1/build

# Include any dependencies generated for this target.
include CMakeFiles/_MyLib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/_MyLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/_MyLib.dir/flags.make

CMakeFiles/_MyLib.dir/Algo.cpp.o: CMakeFiles/_MyLib.dir/flags.make
CMakeFiles/_MyLib.dir/Algo.cpp.o: ../Algo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zwimer/School/OpSys/Project1/Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/_MyLib.dir/Algo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_MyLib.dir/Algo.cpp.o -c /Users/zwimer/School/OpSys/Project1/Project1/Algo.cpp

CMakeFiles/_MyLib.dir/Algo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_MyLib.dir/Algo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zwimer/School/OpSys/Project1/Project1/Algo.cpp > CMakeFiles/_MyLib.dir/Algo.cpp.i

CMakeFiles/_MyLib.dir/Algo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_MyLib.dir/Algo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zwimer/School/OpSys/Project1/Project1/Algo.cpp -o CMakeFiles/_MyLib.dir/Algo.cpp.s

CMakeFiles/_MyLib.dir/Algo.cpp.o.requires:

.PHONY : CMakeFiles/_MyLib.dir/Algo.cpp.o.requires

CMakeFiles/_MyLib.dir/Algo.cpp.o.provides: CMakeFiles/_MyLib.dir/Algo.cpp.o.requires
	$(MAKE) -f CMakeFiles/_MyLib.dir/build.make CMakeFiles/_MyLib.dir/Algo.cpp.o.provides.build
.PHONY : CMakeFiles/_MyLib.dir/Algo.cpp.o.provides

CMakeFiles/_MyLib.dir/Algo.cpp.o.provides.build: CMakeFiles/_MyLib.dir/Algo.cpp.o


CMakeFiles/_MyLib.dir/Event.cpp.o: CMakeFiles/_MyLib.dir/flags.make
CMakeFiles/_MyLib.dir/Event.cpp.o: ../Event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zwimer/School/OpSys/Project1/Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/_MyLib.dir/Event.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_MyLib.dir/Event.cpp.o -c /Users/zwimer/School/OpSys/Project1/Project1/Event.cpp

CMakeFiles/_MyLib.dir/Event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_MyLib.dir/Event.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zwimer/School/OpSys/Project1/Project1/Event.cpp > CMakeFiles/_MyLib.dir/Event.cpp.i

CMakeFiles/_MyLib.dir/Event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_MyLib.dir/Event.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zwimer/School/OpSys/Project1/Project1/Event.cpp -o CMakeFiles/_MyLib.dir/Event.cpp.s

CMakeFiles/_MyLib.dir/Event.cpp.o.requires:

.PHONY : CMakeFiles/_MyLib.dir/Event.cpp.o.requires

CMakeFiles/_MyLib.dir/Event.cpp.o.provides: CMakeFiles/_MyLib.dir/Event.cpp.o.requires
	$(MAKE) -f CMakeFiles/_MyLib.dir/build.make CMakeFiles/_MyLib.dir/Event.cpp.o.provides.build
.PHONY : CMakeFiles/_MyLib.dir/Event.cpp.o.provides

CMakeFiles/_MyLib.dir/Event.cpp.o.provides.build: CMakeFiles/_MyLib.dir/Event.cpp.o


CMakeFiles/_MyLib.dir/Process.cpp.o: CMakeFiles/_MyLib.dir/flags.make
CMakeFiles/_MyLib.dir/Process.cpp.o: ../Process.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zwimer/School/OpSys/Project1/Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/_MyLib.dir/Process.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_MyLib.dir/Process.cpp.o -c /Users/zwimer/School/OpSys/Project1/Project1/Process.cpp

CMakeFiles/_MyLib.dir/Process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_MyLib.dir/Process.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zwimer/School/OpSys/Project1/Project1/Process.cpp > CMakeFiles/_MyLib.dir/Process.cpp.i

CMakeFiles/_MyLib.dir/Process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_MyLib.dir/Process.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zwimer/School/OpSys/Project1/Project1/Process.cpp -o CMakeFiles/_MyLib.dir/Process.cpp.s

CMakeFiles/_MyLib.dir/Process.cpp.o.requires:

.PHONY : CMakeFiles/_MyLib.dir/Process.cpp.o.requires

CMakeFiles/_MyLib.dir/Process.cpp.o.provides: CMakeFiles/_MyLib.dir/Process.cpp.o.requires
	$(MAKE) -f CMakeFiles/_MyLib.dir/build.make CMakeFiles/_MyLib.dir/Process.cpp.o.provides.build
.PHONY : CMakeFiles/_MyLib.dir/Process.cpp.o.provides

CMakeFiles/_MyLib.dir/Process.cpp.o.provides.build: CMakeFiles/_MyLib.dir/Process.cpp.o


# Object files for target _MyLib
_MyLib_OBJECTS = \
"CMakeFiles/_MyLib.dir/Algo.cpp.o" \
"CMakeFiles/_MyLib.dir/Event.cpp.o" \
"CMakeFiles/_MyLib.dir/Process.cpp.o"

# External object files for target _MyLib
_MyLib_EXTERNAL_OBJECTS =

lib_MyLib.dylib: CMakeFiles/_MyLib.dir/Algo.cpp.o
lib_MyLib.dylib: CMakeFiles/_MyLib.dir/Event.cpp.o
lib_MyLib.dylib: CMakeFiles/_MyLib.dir/Process.cpp.o
lib_MyLib.dylib: CMakeFiles/_MyLib.dir/build.make
lib_MyLib.dylib: CMakeFiles/_MyLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zwimer/School/OpSys/Project1/Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library lib_MyLib.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_MyLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/_MyLib.dir/build: lib_MyLib.dylib

.PHONY : CMakeFiles/_MyLib.dir/build

CMakeFiles/_MyLib.dir/requires: CMakeFiles/_MyLib.dir/Algo.cpp.o.requires
CMakeFiles/_MyLib.dir/requires: CMakeFiles/_MyLib.dir/Event.cpp.o.requires
CMakeFiles/_MyLib.dir/requires: CMakeFiles/_MyLib.dir/Process.cpp.o.requires

.PHONY : CMakeFiles/_MyLib.dir/requires

CMakeFiles/_MyLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/_MyLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/_MyLib.dir/clean

CMakeFiles/_MyLib.dir/depend:
	cd /Users/zwimer/School/OpSys/Project1/Project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zwimer/School/OpSys/Project1/Project1 /Users/zwimer/School/OpSys/Project1/Project1 /Users/zwimer/School/OpSys/Project1/Project1/build /Users/zwimer/School/OpSys/Project1/Project1/build /Users/zwimer/School/OpSys/Project1/Project1/build/CMakeFiles/_MyLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/_MyLib.dir/depend

