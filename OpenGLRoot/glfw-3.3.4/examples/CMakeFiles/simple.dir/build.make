# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\joaov\Desktop\glfw-3.3.4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\joaov\Desktop\glfw-3.3.4

# Include any dependencies generated for this target.
include examples/CMakeFiles/simple.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/simple.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/simple.dir/flags.make

examples/CMakeFiles/simple.dir/simple.c.obj: examples/CMakeFiles/simple.dir/flags.make
examples/CMakeFiles/simple.dir/simple.c.obj: examples/CMakeFiles/simple.dir/includes_C.rsp
examples/CMakeFiles/simple.dir/simple.c.obj: examples/simple.c
examples/CMakeFiles/simple.dir/simple.c.obj: examples/CMakeFiles/simple.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\glfw-3.3.4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/simple.dir/simple.c.obj"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/simple.dir/simple.c.obj -MF CMakeFiles\simple.dir\simple.c.obj.d -o CMakeFiles\simple.dir\simple.c.obj -c C:\Users\joaov\Desktop\glfw-3.3.4\examples\simple.c

examples/CMakeFiles/simple.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/simple.c.i"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\glfw-3.3.4\examples\simple.c > CMakeFiles\simple.dir\simple.c.i

examples/CMakeFiles/simple.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/simple.c.s"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\glfw-3.3.4\examples\simple.c -o CMakeFiles\simple.dir\simple.c.s

examples/CMakeFiles/simple.dir/glfw.rc.obj: examples/CMakeFiles/simple.dir/flags.make
examples/CMakeFiles/simple.dir/glfw.rc.obj: examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\glfw-3.3.4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object examples/CMakeFiles/simple.dir/glfw.rc.obj"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) C:\Users\joaov\Desktop\glfw-3.3.4\examples\glfw.rc CMakeFiles\simple.dir\glfw.rc.obj

examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj: examples/CMakeFiles/simple.dir/flags.make
examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj: examples/CMakeFiles/simple.dir/includes_C.rsp
examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj: deps/glad_gl.c
examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj: examples/CMakeFiles/simple.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\glfw-3.3.4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj -MF CMakeFiles\simple.dir\__\deps\glad_gl.c.obj.d -o CMakeFiles\simple.dir\__\deps\glad_gl.c.obj -c C:\Users\joaov\Desktop\glfw-3.3.4\deps\glad_gl.c

examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/__/deps/glad_gl.c.i"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\glfw-3.3.4\deps\glad_gl.c > CMakeFiles\simple.dir\__\deps\glad_gl.c.i

examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/__/deps/glad_gl.c.s"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\glfw-3.3.4\deps\glad_gl.c -o CMakeFiles\simple.dir\__\deps\glad_gl.c.s

# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/simple.c.obj" \
"CMakeFiles/simple.dir/glfw.rc.obj" \
"CMakeFiles/simple.dir/__/deps/glad_gl.c.obj"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

examples/simple.exe: examples/CMakeFiles/simple.dir/simple.c.obj
examples/simple.exe: examples/CMakeFiles/simple.dir/glfw.rc.obj
examples/simple.exe: examples/CMakeFiles/simple.dir/__/deps/glad_gl.c.obj
examples/simple.exe: examples/CMakeFiles/simple.dir/build.make
examples/simple.exe: src/libglfw3.a
examples/simple.exe: examples/CMakeFiles/simple.dir/linklibs.rsp
examples/simple.exe: examples/CMakeFiles/simple.dir/objects1.rsp
examples/simple.exe: examples/CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\joaov\Desktop\glfw-3.3.4\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable simple.exe"
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simple.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/simple.dir/build: examples/simple.exe
.PHONY : examples/CMakeFiles/simple.dir/build

examples/CMakeFiles/simple.dir/clean:
	cd /d C:\Users\joaov\Desktop\glfw-3.3.4\examples && $(CMAKE_COMMAND) -P CMakeFiles\simple.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/simple.dir/clean

examples/CMakeFiles/simple.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\joaov\Desktop\glfw-3.3.4 C:\Users\joaov\Desktop\glfw-3.3.4\examples C:\Users\joaov\Desktop\glfw-3.3.4 C:\Users\joaov\Desktop\glfw-3.3.4\examples C:\Users\joaov\Desktop\glfw-3.3.4\examples\CMakeFiles\simple.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/simple.dir/depend

