# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Boids)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(wxWidgets COMPONENTS net core base gl REQUIRED)


include(${wxWidgets_USE_FILE})


# START GOOGLE TEST:
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src	
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)
				 
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
enable_testing()
add_executable(
	boid_test
	test/vector3d_test.cpp
  test/boid_test.cpp
  test/world_test.cpp
)
target_link_libraries(boid_test gtest_main)
add_test(NAME boid_test COMMAND boid_test)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}, ${GLM_INCLUDE_DIRS})

link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})

add_executable(
  boid_app
	src/main.cpp
  src/Boids3DFrame.cpp
  src/BoidsUI.cpp
  src/shader.cpp
)

target_link_libraries(boid_app
	${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${wxWidgets_LIBRARIES}
)
