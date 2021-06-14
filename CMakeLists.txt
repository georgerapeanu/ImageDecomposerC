cmake_minimum_required(VERSION 3.11)

# Project name and a few useful settings. Other commands can pick up the results
project(
  ImageDecomposer
  VERSION 0.1
  DESCRIPTION "A monte-carlo algorithm to aproximate images with various shapes"
  LANGUAGES CXX)  

find_package( OpenCV REQUIRED )

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

