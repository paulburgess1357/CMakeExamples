cmake_minimum_required(VERSION 3.0.0)

project(Test_MathLibrary_Pkg VERSION 1.0.0)

# This must be set if you used a custom cmake location (normally from cmd line)
# How to make this work with only supplying:
# set(CMAKE_PREFIX_PATH "C:/users/paulb/documents/CLibs") ???? e.g. from command line????
# set(CMAKE_PREFIX_PATH "C:/users/paulb/documents/CLibs/lib/libmath")
# Copy paste and build from cmd line: 
# cmake -D "CMAKE_INSTALL_PREFIX:PATH=C:/users/paulb/documents/CLibs/lib" ..

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc /std:c++latest")

# Just for testing if main.cpp can find library (normally I set this from command line)
# set(CMAKE_PREFIX_PATH "C:/users/paulb/documents/CLibs/lib")
find_package(MathLibrary) # Searches modeule mode then config mode.  You can specify which mode you want as well.

if(MathLibrary_FOUND)
	message("my_math library found!")
	add_executable(math_test main.cpp)
	target_link_libraries(math_test MathLibrary)
else()
	message(FATAL_ERROR "MathLibrary was not found!!")
endif()