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
CMAKE_SOURCE_DIR = C:\Users\joaov\Desktop\lpng1637

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\joaov\Desktop\lpng1637

# Include any dependencies generated for this target.
include CMakeFiles/png_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/png_static.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/png_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/png_static.dir/flags.make

CMakeFiles/png_static.dir/png.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/png.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/png.c.obj: png.c
CMakeFiles/png_static.dir/png.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/png_static.dir/png.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/png.c.obj -MF CMakeFiles\png_static.dir\png.c.obj.d -o CMakeFiles\png_static.dir\png.c.obj -c C:\Users\joaov\Desktop\lpng1637\png.c

CMakeFiles/png_static.dir/png.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/png.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\png.c > CMakeFiles\png_static.dir\png.c.i

CMakeFiles/png_static.dir/png.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/png.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\png.c -o CMakeFiles\png_static.dir\png.c.s

CMakeFiles/png_static.dir/pngerror.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngerror.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngerror.c.obj: pngerror.c
CMakeFiles/png_static.dir/pngerror.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/png_static.dir/pngerror.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngerror.c.obj -MF CMakeFiles\png_static.dir\pngerror.c.obj.d -o CMakeFiles\png_static.dir\pngerror.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngerror.c

CMakeFiles/png_static.dir/pngerror.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngerror.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngerror.c > CMakeFiles\png_static.dir\pngerror.c.i

CMakeFiles/png_static.dir/pngerror.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngerror.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngerror.c -o CMakeFiles\png_static.dir\pngerror.c.s

CMakeFiles/png_static.dir/pngget.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngget.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngget.c.obj: pngget.c
CMakeFiles/png_static.dir/pngget.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/png_static.dir/pngget.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngget.c.obj -MF CMakeFiles\png_static.dir\pngget.c.obj.d -o CMakeFiles\png_static.dir\pngget.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngget.c

CMakeFiles/png_static.dir/pngget.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngget.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngget.c > CMakeFiles\png_static.dir\pngget.c.i

CMakeFiles/png_static.dir/pngget.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngget.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngget.c -o CMakeFiles\png_static.dir\pngget.c.s

CMakeFiles/png_static.dir/pngmem.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngmem.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngmem.c.obj: pngmem.c
CMakeFiles/png_static.dir/pngmem.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/png_static.dir/pngmem.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngmem.c.obj -MF CMakeFiles\png_static.dir\pngmem.c.obj.d -o CMakeFiles\png_static.dir\pngmem.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngmem.c

CMakeFiles/png_static.dir/pngmem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngmem.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngmem.c > CMakeFiles\png_static.dir\pngmem.c.i

CMakeFiles/png_static.dir/pngmem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngmem.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngmem.c -o CMakeFiles\png_static.dir\pngmem.c.s

CMakeFiles/png_static.dir/pngpread.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngpread.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngpread.c.obj: pngpread.c
CMakeFiles/png_static.dir/pngpread.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/png_static.dir/pngpread.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngpread.c.obj -MF CMakeFiles\png_static.dir\pngpread.c.obj.d -o CMakeFiles\png_static.dir\pngpread.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngpread.c

CMakeFiles/png_static.dir/pngpread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngpread.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngpread.c > CMakeFiles\png_static.dir\pngpread.c.i

CMakeFiles/png_static.dir/pngpread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngpread.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngpread.c -o CMakeFiles\png_static.dir\pngpread.c.s

CMakeFiles/png_static.dir/pngread.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngread.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngread.c.obj: pngread.c
CMakeFiles/png_static.dir/pngread.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/png_static.dir/pngread.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngread.c.obj -MF CMakeFiles\png_static.dir\pngread.c.obj.d -o CMakeFiles\png_static.dir\pngread.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngread.c

CMakeFiles/png_static.dir/pngread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngread.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngread.c > CMakeFiles\png_static.dir\pngread.c.i

CMakeFiles/png_static.dir/pngread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngread.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngread.c -o CMakeFiles\png_static.dir\pngread.c.s

CMakeFiles/png_static.dir/pngrio.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngrio.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngrio.c.obj: pngrio.c
CMakeFiles/png_static.dir/pngrio.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/png_static.dir/pngrio.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngrio.c.obj -MF CMakeFiles\png_static.dir\pngrio.c.obj.d -o CMakeFiles\png_static.dir\pngrio.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngrio.c

CMakeFiles/png_static.dir/pngrio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngrio.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngrio.c > CMakeFiles\png_static.dir\pngrio.c.i

CMakeFiles/png_static.dir/pngrio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngrio.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngrio.c -o CMakeFiles\png_static.dir\pngrio.c.s

CMakeFiles/png_static.dir/pngrtran.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngrtran.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngrtran.c.obj: pngrtran.c
CMakeFiles/png_static.dir/pngrtran.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/png_static.dir/pngrtran.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngrtran.c.obj -MF CMakeFiles\png_static.dir\pngrtran.c.obj.d -o CMakeFiles\png_static.dir\pngrtran.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngrtran.c

CMakeFiles/png_static.dir/pngrtran.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngrtran.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngrtran.c > CMakeFiles\png_static.dir\pngrtran.c.i

CMakeFiles/png_static.dir/pngrtran.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngrtran.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngrtran.c -o CMakeFiles\png_static.dir\pngrtran.c.s

CMakeFiles/png_static.dir/pngrutil.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngrutil.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngrutil.c.obj: pngrutil.c
CMakeFiles/png_static.dir/pngrutil.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/png_static.dir/pngrutil.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngrutil.c.obj -MF CMakeFiles\png_static.dir\pngrutil.c.obj.d -o CMakeFiles\png_static.dir\pngrutil.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngrutil.c

CMakeFiles/png_static.dir/pngrutil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngrutil.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngrutil.c > CMakeFiles\png_static.dir\pngrutil.c.i

CMakeFiles/png_static.dir/pngrutil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngrutil.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngrutil.c -o CMakeFiles\png_static.dir\pngrutil.c.s

CMakeFiles/png_static.dir/pngset.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngset.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngset.c.obj: pngset.c
CMakeFiles/png_static.dir/pngset.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/png_static.dir/pngset.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngset.c.obj -MF CMakeFiles\png_static.dir\pngset.c.obj.d -o CMakeFiles\png_static.dir\pngset.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngset.c

CMakeFiles/png_static.dir/pngset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngset.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngset.c > CMakeFiles\png_static.dir\pngset.c.i

CMakeFiles/png_static.dir/pngset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngset.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngset.c -o CMakeFiles\png_static.dir\pngset.c.s

CMakeFiles/png_static.dir/pngtrans.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngtrans.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngtrans.c.obj: pngtrans.c
CMakeFiles/png_static.dir/pngtrans.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/png_static.dir/pngtrans.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngtrans.c.obj -MF CMakeFiles\png_static.dir\pngtrans.c.obj.d -o CMakeFiles\png_static.dir\pngtrans.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngtrans.c

CMakeFiles/png_static.dir/pngtrans.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngtrans.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngtrans.c > CMakeFiles\png_static.dir\pngtrans.c.i

CMakeFiles/png_static.dir/pngtrans.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngtrans.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngtrans.c -o CMakeFiles\png_static.dir\pngtrans.c.s

CMakeFiles/png_static.dir/pngwio.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngwio.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngwio.c.obj: pngwio.c
CMakeFiles/png_static.dir/pngwio.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/png_static.dir/pngwio.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngwio.c.obj -MF CMakeFiles\png_static.dir\pngwio.c.obj.d -o CMakeFiles\png_static.dir\pngwio.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngwio.c

CMakeFiles/png_static.dir/pngwio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngwio.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngwio.c > CMakeFiles\png_static.dir\pngwio.c.i

CMakeFiles/png_static.dir/pngwio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngwio.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngwio.c -o CMakeFiles\png_static.dir\pngwio.c.s

CMakeFiles/png_static.dir/pngwrite.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngwrite.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngwrite.c.obj: pngwrite.c
CMakeFiles/png_static.dir/pngwrite.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/png_static.dir/pngwrite.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngwrite.c.obj -MF CMakeFiles\png_static.dir\pngwrite.c.obj.d -o CMakeFiles\png_static.dir\pngwrite.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngwrite.c

CMakeFiles/png_static.dir/pngwrite.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngwrite.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngwrite.c > CMakeFiles\png_static.dir\pngwrite.c.i

CMakeFiles/png_static.dir/pngwrite.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngwrite.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngwrite.c -o CMakeFiles\png_static.dir\pngwrite.c.s

CMakeFiles/png_static.dir/pngwtran.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngwtran.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngwtran.c.obj: pngwtran.c
CMakeFiles/png_static.dir/pngwtran.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/png_static.dir/pngwtran.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngwtran.c.obj -MF CMakeFiles\png_static.dir\pngwtran.c.obj.d -o CMakeFiles\png_static.dir\pngwtran.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngwtran.c

CMakeFiles/png_static.dir/pngwtran.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngwtran.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngwtran.c > CMakeFiles\png_static.dir\pngwtran.c.i

CMakeFiles/png_static.dir/pngwtran.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngwtran.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngwtran.c -o CMakeFiles\png_static.dir\pngwtran.c.s

CMakeFiles/png_static.dir/pngwutil.c.obj: CMakeFiles/png_static.dir/flags.make
CMakeFiles/png_static.dir/pngwutil.c.obj: CMakeFiles/png_static.dir/includes_C.rsp
CMakeFiles/png_static.dir/pngwutil.c.obj: pngwutil.c
CMakeFiles/png_static.dir/pngwutil.c.obj: CMakeFiles/png_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/png_static.dir/pngwutil.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/png_static.dir/pngwutil.c.obj -MF CMakeFiles\png_static.dir\pngwutil.c.obj.d -o CMakeFiles\png_static.dir\pngwutil.c.obj -c C:\Users\joaov\Desktop\lpng1637\pngwutil.c

CMakeFiles/png_static.dir/pngwutil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/png_static.dir/pngwutil.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\joaov\Desktop\lpng1637\pngwutil.c > CMakeFiles\png_static.dir\pngwutil.c.i

CMakeFiles/png_static.dir/pngwutil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/png_static.dir/pngwutil.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\joaov\Desktop\lpng1637\pngwutil.c -o CMakeFiles\png_static.dir\pngwutil.c.s

# Object files for target png_static
png_static_OBJECTS = \
"CMakeFiles/png_static.dir/png.c.obj" \
"CMakeFiles/png_static.dir/pngerror.c.obj" \
"CMakeFiles/png_static.dir/pngget.c.obj" \
"CMakeFiles/png_static.dir/pngmem.c.obj" \
"CMakeFiles/png_static.dir/pngpread.c.obj" \
"CMakeFiles/png_static.dir/pngread.c.obj" \
"CMakeFiles/png_static.dir/pngrio.c.obj" \
"CMakeFiles/png_static.dir/pngrtran.c.obj" \
"CMakeFiles/png_static.dir/pngrutil.c.obj" \
"CMakeFiles/png_static.dir/pngset.c.obj" \
"CMakeFiles/png_static.dir/pngtrans.c.obj" \
"CMakeFiles/png_static.dir/pngwio.c.obj" \
"CMakeFiles/png_static.dir/pngwrite.c.obj" \
"CMakeFiles/png_static.dir/pngwtran.c.obj" \
"CMakeFiles/png_static.dir/pngwutil.c.obj"

# External object files for target png_static
png_static_EXTERNAL_OBJECTS =

libpng16.a: CMakeFiles/png_static.dir/png.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngerror.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngget.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngmem.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngpread.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngread.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngrio.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngrtran.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngrutil.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngset.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngtrans.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngwio.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngwrite.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngwtran.c.obj
libpng16.a: CMakeFiles/png_static.dir/pngwutil.c.obj
libpng16.a: CMakeFiles/png_static.dir/build.make
libpng16.a: CMakeFiles/png_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\joaov\Desktop\lpng1637\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C static library libpng16.a"
	$(CMAKE_COMMAND) -P CMakeFiles\png_static.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\png_static.dir\link.txt --verbose=$(VERBOSE)
	"C:\Program Files\CMake\bin\cmake.exe" -E copy_if_different libpng16.a C:/Users/joaov/Desktop/lpng1637/libpng.a

# Rule to build all files generated by this target.
CMakeFiles/png_static.dir/build: libpng16.a
.PHONY : CMakeFiles/png_static.dir/build

CMakeFiles/png_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\png_static.dir\cmake_clean.cmake
.PHONY : CMakeFiles/png_static.dir/clean

CMakeFiles/png_static.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\joaov\Desktop\lpng1637 C:\Users\joaov\Desktop\lpng1637 C:\Users\joaov\Desktop\lpng1637 C:\Users\joaov\Desktop\lpng1637 C:\Users\joaov\Desktop\lpng1637\CMakeFiles\png_static.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/png_static.dir/depend

