cmake_minimum_required(VERSION 3.10.2)

# set(CMAKE_BUILD_TYPE Debug)

project(Abalone)

add_executable(${PROJECT_NAME}
main.cpp
)

target_link_libraries (${PROJECT_NAME}
	sfml-graphics
	sfml-window
	sfml-system
	-lX11
)
