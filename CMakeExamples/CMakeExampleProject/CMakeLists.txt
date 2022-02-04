# Set min version
cmake_minimum_required(VERSION 3.0.0)

# Project name and optional version number
# This will be the solution name is visual studio
message(STATUS "Building Cmake Example Solution!!!")

# Not sure if this is solution or project...
# If its solution, how do i make an executable project?
# If its project, how do I name the solution?
project(CMakeExampleSolution VERSION 1.0.0)

# Specify some flags for the compilier
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /std:c++latest")

# Note: If you wanted to build SHARED libraries instead of STATIC:
# 1) set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
# 2) Change your add_library() function calls to SHARED instead of STATIC
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
# Setting the above to true ensures that cmake creates the .lib file which
# windows requires (even for dll's).  The .lib file contains the exported
# symbols (and you can avoid doing the __declspec stuff)


# Specify global cmake settings.  You can also do this per target instead.  I
# believe this is considered 'global' due to the scope of these being set
# in the main cmake script
# E.g. set_target_properties 
# Cmake will implicitly add Debug or Release folders after the entire folder name

# Definitions:
# CMAKE_SOURCE_DIR: This is the directory which contains the top-level CMakeLists.txt, i.e. the top level source directory
# CMAKE_BINARY_DIR: This is the top level directory of your build tree
# Normally empty, but if you define them CMAKE will use them:
# CMAKE_ARCHIVE_OUTPUT_DIRECTORY: This is the static library file (e.g. .lib)
# CMAKE_LIBRARY_OUTPUT_DIRECTORY: This is the .dll types of output
# CMAKE_RUNTIME_OUTPUT_DIRECTORY: This is the .exe type of file

# Set if you want more control over output locations:
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin") 
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")

# Process additional cmake files (e.g. other static/dynamic libs)
add_subdirectory(libmath)
#add_subdirectory(libprint)
#add_subdirectory(libwaffle)

# Create executable
add_executable(cmake_example_project_executable 
main.cpp)

# Link target libraries to an executable:
# E.g. Link libmath.lib to cmake_example_project_executable.exe
# Cmake will look at each targets (libmath.lib, libprint.lib, etc.) properties.
# These properties may be visible to the executable target DEPENDING on the 
# scope.  For example, in libmath/CMakeLists.txt we set a property: target_include_directories(MathLibrary PRIVATE libmath)
# that makes the folder 'libmath' visible to the headers and cpp files for that library (see AllMath.cpp).  If we wanted
# this property to be in this location as well, we can simply change it to PUBLIC

# Set include directory for desired target (in this case its the executable):
# This is relative to the CMakeLists.txt file you are working in
target_include_directories(cmake_example_project_executable 
	PRIVATE 
	libmath)

# =============== Linker Tests ===================
# Linker tests for libraries created in cmake submodules

# ==== When Setting Variables Above: ====
# CMAKE_ARCHIVE_OUTPUT_DIRECTORY
# CMAKE_LIBRARY_OUTPUT_DIRECTORY
# CMAKE_RUNTIME_OUTPUT_DIRECTORY

# Example 1:
# link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
# target_link_libraries(cmake_example_project_executable PRIVATE MathLibrary)

# Example 2:
# target_link_libraries(cmake_example_project_executable PRIVATE MathLibrary)

# ==== Not setting above variables ====
# Example 3
target_link_libraries(cmake_example_project_executable PRIVATE MathLibrary)

# For the above, I think setting the above variables impacts where target_link_libraries
# looks for the lib files.  In both cases, the same statement (example 2 and example 3) worked.
# Example 2 set those variables for output.  Example 3 did not.  Internally CMAKE must keep
# track of it.

# ================ External Libraries ===================

# find_package() is preferred to find_library().  find_package() will
# look for MathLibrary-config in the location: CMAKE_PREFIX_PATH.
# This config file should allow it to find headers and .lib for MathLibrary

# Keeping find_library notes, but prefer find_package() instead:

# External library includes (i.e. not submodules)
# Set linker include directories:
# Not recommended way:
# - Link directories is just like properties -> linker -> additional library path
# link_directories(Path Here)
# target_link_directories(Path Here)
# 
# target_link_libraries(cmake_example_project_executable PRIVATE MathLibrary)

# Recommended link approach:
# Use 'find_library' and store the absolute path output.  Use this in target_link_libraries
# - If you had specified a custom directory: 
#   - find_library(MathLibrary_Location MathLibrary HINTS < library location path here >)
#   - target_link_libraries(cmake_example_project_executable PRIVATE ${MathLibrary_Location})