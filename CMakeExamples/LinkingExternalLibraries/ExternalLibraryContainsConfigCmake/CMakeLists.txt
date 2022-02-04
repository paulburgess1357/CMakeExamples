cmake_minimum_required(VERSION 3.0.0)

project(DisplayImageExternalPackageExample)

find_package(OpenCV REQUIRED) # If you don't add required, CMake will treat it as optional
# OpenCV -> Cmake will look for OpenCVConfig.cmake (so its case sensitive)

add_executable(DisplayImageExecutable main.cpp)

target_include_directories(DisplayImageExecutable PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(DisplayImageExecutable PRIVATE ${OpenCV_LIBS})

message("OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
message("OpenCV include libraries: ${OpenCV_LIBS}")