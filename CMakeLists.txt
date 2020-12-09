cmake_minimum_required(VERSION 3.19)

project(SnowfallEngine VERSION 1.0.0)

file(GLOB_RECURSE SRC "src/*.hpp" "src/*.cpp")

# Flags for debug build
set(
	CMAKE_CXX_FLAGS_DEBUG 
	"${CMAKE_CXX_FLAGS_DEBUG} -Wall"
)
# Flags for Release build
set(
	CMAKE_CXX_FLAGS_RELEASE 
	"${CMAKE_CXX_FLAGS_RELEASE} -Wall"
)

# Set C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_subdirectory(src)
add_subdirectory(build)