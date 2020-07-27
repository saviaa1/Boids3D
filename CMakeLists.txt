# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Boids)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(wxWidgets COMPONENTS net core base gl REQUIRED)


include(${wxWidgets_USE_FILE})

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(
    boid_app
	src/main.cpp
)

target_link_libraries(boid_app
	${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${wxWidgets_LIBRARIES}
)
