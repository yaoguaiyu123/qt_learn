# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /run/media/root/study/github_repository/qt_learn/qt37

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug

# Include any dependencies generated for this target.
include CMakeFiles/qt37.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qt37.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qt37.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qt37.dir/flags.make

CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o: CMakeFiles/qt37.dir/flags.make
CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o: qt37_autogen/mocs_compilation.cpp
CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o: CMakeFiles/qt37.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o -MF CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o -c /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/qt37_autogen/mocs_compilation.cpp

CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/qt37_autogen/mocs_compilation.cpp > CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.i

CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/qt37_autogen/mocs_compilation.cpp -o CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.s

CMakeFiles/qt37.dir/mainwindow.cpp.o: CMakeFiles/qt37.dir/flags.make
CMakeFiles/qt37.dir/mainwindow.cpp.o: /run/media/root/study/github_repository/qt_learn/qt37/mainwindow.cpp
CMakeFiles/qt37.dir/mainwindow.cpp.o: CMakeFiles/qt37.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/qt37.dir/mainwindow.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt37.dir/mainwindow.cpp.o -MF CMakeFiles/qt37.dir/mainwindow.cpp.o.d -o CMakeFiles/qt37.dir/mainwindow.cpp.o -c /run/media/root/study/github_repository/qt_learn/qt37/mainwindow.cpp

CMakeFiles/qt37.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/qt37.dir/mainwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/root/study/github_repository/qt_learn/qt37/mainwindow.cpp > CMakeFiles/qt37.dir/mainwindow.cpp.i

CMakeFiles/qt37.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/qt37.dir/mainwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/root/study/github_repository/qt_learn/qt37/mainwindow.cpp -o CMakeFiles/qt37.dir/mainwindow.cpp.s

CMakeFiles/qt37.dir/main.cpp.o: CMakeFiles/qt37.dir/flags.make
CMakeFiles/qt37.dir/main.cpp.o: /run/media/root/study/github_repository/qt_learn/qt37/main.cpp
CMakeFiles/qt37.dir/main.cpp.o: CMakeFiles/qt37.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/qt37.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt37.dir/main.cpp.o -MF CMakeFiles/qt37.dir/main.cpp.o.d -o CMakeFiles/qt37.dir/main.cpp.o -c /run/media/root/study/github_repository/qt_learn/qt37/main.cpp

CMakeFiles/qt37.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/qt37.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/root/study/github_repository/qt_learn/qt37/main.cpp > CMakeFiles/qt37.dir/main.cpp.i

CMakeFiles/qt37.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/qt37.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/root/study/github_repository/qt_learn/qt37/main.cpp -o CMakeFiles/qt37.dir/main.cpp.s

# Object files for target qt37
qt37_OBJECTS = \
"CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/qt37.dir/mainwindow.cpp.o" \
"CMakeFiles/qt37.dir/main.cpp.o"

# External object files for target qt37
qt37_EXTERNAL_OBJECTS =

qt37: CMakeFiles/qt37.dir/qt37_autogen/mocs_compilation.cpp.o
qt37: CMakeFiles/qt37.dir/mainwindow.cpp.o
qt37: CMakeFiles/qt37.dir/main.cpp.o
qt37: CMakeFiles/qt37.dir/build.make
qt37: /opt/Qt/6.5.3/gcc_64/lib/libQt6MultimediaWidgets.so.6.5.3
qt37: /opt/Qt/6.5.3/gcc_64/lib/libQt6Multimedia.so.6.5.3
qt37: /opt/Qt/6.5.3/gcc_64/lib/libQt6Network.so.6.5.3
qt37: /opt/Qt/6.5.3/gcc_64/lib/libQt6Widgets.so.6.5.3
qt37: /opt/Qt/6.5.3/gcc_64/lib/libQt6Gui.so.6.5.3
qt37: /opt/Qt/6.5.3/gcc_64/lib/libQt6Core.so.6.5.3
qt37: /usr/lib/libGLX.so
qt37: /usr/lib/libOpenGL.so
qt37: CMakeFiles/qt37.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable qt37"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qt37.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qt37.dir/build: qt37
.PHONY : CMakeFiles/qt37.dir/build

CMakeFiles/qt37.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt37.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt37.dir/clean

CMakeFiles/qt37.dir/depend:
	cd /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/root/study/github_repository/qt_learn/qt37 /run/media/root/study/github_repository/qt_learn/qt37 /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug /run/media/root/study/github_repository/qt_learn/build-qt37-C_C_2024_03_19-Debug/CMakeFiles/qt37.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/qt37.dir/depend

