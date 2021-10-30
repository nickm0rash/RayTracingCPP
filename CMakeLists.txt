cmake_minimum_required(VERSION 3.13)
project(RayTracingCPP
	VERSION
	   1.0
	DESCRIPTION
	   "Ray tracing with C++"
	LANGUAGES
	   CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(raytracer main.cpp output.cpp vecmath.cpp ray.cpp sphere.cpp material.cpp cam.cpp)