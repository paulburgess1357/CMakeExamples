# This cmake file is responsible for managing the MathLibary
# This is relative to the current CmakeLists.txt file

# To add one cpp file at a time:
add_library(MathLibrary STATIC
"libmath/AdditionFunctions/Addition.cpp"
"libmath/DivideFunctions/Divide.cpp"
"libmath/MultiplyFunctions/Multiply.cpp"
"libmath/SubtractionFunctions/Subtract.cpp"
"libmath/AllMath/AllMath.cpp")

# To add all cpp files...

# Set debug postfix (e.g. MathLibraryd.lib; Mathlibrary.lib)
set_target_properties(MathLibrary PROPERTIES DEBUG_POSTFIX d)


# ==================== Setting includes for use within this solution ====================
#                     (and potentially target depending on scope) only

# This is where we would normally set the include folder path in the properties -> c/c++ -> additional include directories

# === Example 1 ===
# - target_include_directories(MathLibrary PRIVATE libmath)
#   - Make the folder 'libmath' in this CMakeLists directory visible to all libmath files

# === Example 2 ===
# - target_include_directories(MathLibrary PRIVATE libmath/AdditionFunctions)
#   - Make the folder libmath/AdditionFunctions visible.  This allows me to say 'include "Addition.h"' in any file used in this library

# === Example 3 ===
# - target_include_directories(MathLibrary PRIVATE libmath libmath/AdditionFunctions)
#   - Both locations are included


# ==================== Setting includes for use in and outside this solution ====================
# E.g. Use in this solution, but export the package for use elsewhere:

# The following applies when using 'INSTALL(EXPORT)' and find_package()
# Install location is based on: CMAKE_INSTALL_PREFIX
# INSTALL(EXPORT)
#  - Creates the cmake config file and installs it
# find_package(ABC) 
# - Looks for: ABC-config.cmake located in the users CMAKE_INSTALL_PREFIX location
# - find_package(ABC) ----> /usr/local/lib/ABC/ABC-config.cmake 

# INSTALL_INTERFACE: 
# - Necessary when target is exported using install(EXPORT).  Used for when you are exporting the library for other applications to use.
# - In this example, we are copying all headers (along with directory structure) by copying libmath into: ${CMAKE_INSTALL_PREFIX}/include,
#   so the install location looks like this: C:\Users\paulb\Documents\CLibs\include\libmath.  When we use this package in another program
#   we can say #include "AdditionFunctions/Addition.h".

# BUILD_INTERFACE: 
# - Necessary when the target (MathLibrary) is used by another target (cmake_example_project_executable) in the same build system.
# - For example, in the current build, it impacts what AllMath.cpp can include.  It is allowing us to say: #include "AdditionFunctions/Addition.h"

target_include_directories(MathLibrary PUBLIC   
    $<INSTALL_INTERFACE:include/libmath> # Must match install below????? I'm copying libmath folder into the cmake_install_prefix location but putting it in an include folder...'
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libmath> # Impacts allMath.cpp what headers it can include.... so I don't think i want include/libmath like the above.'
)

# Rule of thumb (mine):
# 1) If exporting the package to other projects that will use find_package(), do the above with PUBLIC
# 2) If using it internally only, use the original method (no generator expressions)

    


# ===================  Package Installation ===================

# === Default Install Locations ===
# CMAKE_INSTALL_PREFIX evaluates to:
#  - Unix: /usr/local -> E.g. /usr/local/include/package_name_here; /usr/local/lib/package_name_here
#  - Windows: c:/Program Files/${PROJECT_NAME}
#  - To override:
#    - cmake -D "CMAKE_INSTALL_PREFIX:PATH=C:/users/paulb/desktop/waffle" ..

# ========== File Copying ==========
# Various methods for copying installation files:
# // https://stackoverflow.com/questions/11096471/how-can-i-install-a-hierarchy-of-files-using-cmake/67883070#67883070

# === Copy individual files ===
# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libmath/AdditionFunctions/Addition.h DESTINATION C:/Users/paulb/Desktop)

# Install to 'CMAKE_INSTALL_PREFIX' which is platform dependent (and user can change during cmake file generation shown above):
# E.g. Windows: C:/Program Files/${PROJECT_NAME}
# install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libmath/AdditionFunctions/Addition.h DESTINATION ${CMAKE_INSTALL_PREFIX})

# === Copy Entire Directory: ===
# install(DIRECTORY libmath/ DESTINATION ${CMAKE_INSTALL_PREFIX}/paulddddd)
# This will make a folder: C:\Program Files (x86)\CMakeExampleSolution\paulddddd and place all folders/files from libmath into that location


# ********** Copy Headers **********
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libmath DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN "*.h")
# Copy Entire Directory and keep structure (headers only); Create include folder if it doens't exist'

# *********** Copy .lib ************
# install(TARGETS MathLibrary DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# To Copy and Prepare for find_package() for future use
set(LIB_INSTALL_LOCATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS MathLibrary EXPORT math_library_export DESTINATION ${LIB_INSTALL_LOCATION})
install(EXPORT math_library_export FILE MathLibrary-config.cmake DESTINATION ${LIB_INSTALL_LOCATION})

# ***** Example of output: *****
# cmake -D "CMAKE_INSTALL_PREFIX:PATH=C:/users/paulb/documents/CLibs" ..

# Header folders will be in: C:\Users\paulb\Documents\CLibs\include\libmath\   # (because i copy the entire directory libmath above)
#                            - AdditionFunctions\
#                            - DivideFunctions\
#                            - etc.
# Lib files will be in: C:\Users\paulb\Documents\CLibs\lib\MathLibrary.lib
# Config file will be in: C:\Users\paulb\Documents\CLibs\lib\libmath\MathLibrary-config.cmake
#  - Config file is used by other applications when they use the command find_package()

