cmake_minimum_required(VERSION 3.10)

project(Colorful_IO VERSION 1.0 LANGUAGES CXX)




#Enable testing
enable_testing()

#Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add the main library project
add_subdirectory(src)

#Add unit tests
add_subdirectory(tests)