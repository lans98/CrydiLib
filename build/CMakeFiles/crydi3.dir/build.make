# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build

# Include any dependencies generated for this target.
include CMakeFiles/crydi3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crydi3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crydi3.dir/flags.make

CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o: CMakeFiles/crydi3.dir/flags.make
CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o: ../src/crydi3_tools.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o -c /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/crydi3_tools.cc

CMakeFiles/crydi3.dir/src/crydi3_tools.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crydi3.dir/src/crydi3_tools.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/crydi3_tools.cc > CMakeFiles/crydi3.dir/src/crydi3_tools.cc.i

CMakeFiles/crydi3.dir/src/crydi3_tools.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crydi3.dir/src/crydi3_tools.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/crydi3_tools.cc -o CMakeFiles/crydi3.dir/src/crydi3_tools.cc.s

CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.requires:

.PHONY : CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.requires

CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.provides: CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.requires
	$(MAKE) -f CMakeFiles/crydi3.dir/build.make CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.provides.build
.PHONY : CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.provides

CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.provides.build: CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o


CMakeFiles/crydi3.dir/src/dynamic_int.cc.o: CMakeFiles/crydi3.dir/flags.make
CMakeFiles/crydi3.dir/src/dynamic_int.cc.o: ../src/dynamic_int.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/crydi3.dir/src/dynamic_int.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crydi3.dir/src/dynamic_int.cc.o -c /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/dynamic_int.cc

CMakeFiles/crydi3.dir/src/dynamic_int.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crydi3.dir/src/dynamic_int.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/dynamic_int.cc > CMakeFiles/crydi3.dir/src/dynamic_int.cc.i

CMakeFiles/crydi3.dir/src/dynamic_int.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crydi3.dir/src/dynamic_int.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/dynamic_int.cc -o CMakeFiles/crydi3.dir/src/dynamic_int.cc.s

CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.requires:

.PHONY : CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.requires

CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.provides: CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.requires
	$(MAKE) -f CMakeFiles/crydi3.dir/build.make CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.provides.build
.PHONY : CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.provides

CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.provides.build: CMakeFiles/crydi3.dir/src/dynamic_int.cc.o


CMakeFiles/crydi3.dir/src/primes_sieve.cc.o: CMakeFiles/crydi3.dir/flags.make
CMakeFiles/crydi3.dir/src/primes_sieve.cc.o: ../src/primes_sieve.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/crydi3.dir/src/primes_sieve.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crydi3.dir/src/primes_sieve.cc.o -c /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/primes_sieve.cc

CMakeFiles/crydi3.dir/src/primes_sieve.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crydi3.dir/src/primes_sieve.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/primes_sieve.cc > CMakeFiles/crydi3.dir/src/primes_sieve.cc.i

CMakeFiles/crydi3.dir/src/primes_sieve.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crydi3.dir/src/primes_sieve.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/src/primes_sieve.cc -o CMakeFiles/crydi3.dir/src/primes_sieve.cc.s

CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.requires:

.PHONY : CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.requires

CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.provides: CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.requires
	$(MAKE) -f CMakeFiles/crydi3.dir/build.make CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.provides.build
.PHONY : CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.provides

CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.provides.build: CMakeFiles/crydi3.dir/src/primes_sieve.cc.o


# Object files for target crydi3
crydi3_OBJECTS = \
"CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o" \
"CMakeFiles/crydi3.dir/src/dynamic_int.cc.o" \
"CMakeFiles/crydi3.dir/src/primes_sieve.cc.o"

# External object files for target crydi3
crydi3_EXTERNAL_OBJECTS =

libcrydi3.so: CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o
libcrydi3.so: CMakeFiles/crydi3.dir/src/dynamic_int.cc.o
libcrydi3.so: CMakeFiles/crydi3.dir/src/primes_sieve.cc.o
libcrydi3.so: CMakeFiles/crydi3.dir/build.make
libcrydi3.so: CMakeFiles/crydi3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libcrydi3.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crydi3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crydi3.dir/build: libcrydi3.so

.PHONY : CMakeFiles/crydi3.dir/build

CMakeFiles/crydi3.dir/requires: CMakeFiles/crydi3.dir/src/crydi3_tools.cc.o.requires
CMakeFiles/crydi3.dir/requires: CMakeFiles/crydi3.dir/src/dynamic_int.cc.o.requires
CMakeFiles/crydi3.dir/requires: CMakeFiles/crydi3.dir/src/primes_sieve.cc.o.requires

.PHONY : CMakeFiles/crydi3.dir/requires

CMakeFiles/crydi3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crydi3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crydi3.dir/clean

CMakeFiles/crydi3.dir/depend:
	cd /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build /home/kevin/Documents/Programming/C++/Criptografia/CrydiLib/build/CMakeFiles/crydi3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crydi3.dir/depend
