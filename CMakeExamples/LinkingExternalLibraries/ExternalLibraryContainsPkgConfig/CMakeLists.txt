cmake_minimum_required(VERSION 3.0.0)
project(PkgConfigExample)

find_package(PkgConfig REQUIRED)  # This is a root cmake thing.  It gives us the following command:

# looks for .pc files 
# we manually found \\wsl$\Ubuntu\usr\lib\x86_64-linux-gnu\pkgconfig\gtk+-3.0.pc)
# this does the same
# In that file, it has information for include directories: prefix=/usr; includedir=${prefix}/include; Cflags: -I${includedir}/gtk-3.0 
# If the file is found, it will set these: GTK3_LIBRARIES and GTK3_INCLUDE_DIRS cmake variables

pkg_check_modules(GTK3 REQUIRED gtk+-3.0) # last param is the .pc file name (shown above); Not sure how you would know GTK3 in the beginning

# GTK3 is just a prefix, and it can be ANY unique keyword you want.
# This GTK3 is used below in the variables: ${GTK3_INCLUDE_DIRS} & ${GTK3_LIBRARIES}
# you could have used waffle above.  Then you would get: ${waffle_INCLUDE_DIRS} & ${waffle_LIBRARIES}


# *** note that the above 'pkg_check_modules' was able to find the gtk+-3.0.pc file easily because it was in the standard location.
#     If it was in a different place, you'd have to help it out by updating the following:
# CMAKE_PREFIX_PATH or PKG_CONFIG_PATH.   Make sure you always APPEND to it, not overwrite it.  
# DONT DO THIS: set(CMAKE_PREFIX_PATH "c:/users/paulb/documents")
# DO:
#   set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH "c:/users/paulb/documents"})
#   list(APPEND CMAKE_PREFIX_PATH "c:/users/paulb/documents")
#   set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:c:/users/paulb/documents")
# You only need to append one of the above.  I think CMAKE_PREFIX_PATH is the easiest.
# I think this has to be done prior to pkg_check_modules.  Howver, the video example did it before pkg_package(PkgConfig REQUIRED); -line 3


add_executable(${PROJECT_NAME}_app main.cpp)

target_include_directories(${PROJECT_NAME}_app PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_app PRIVATE ${GTK3_LIBRARIES})