# C++ 3D Boids

This project implements a 3D version of steering behaviors for autonomous characters based on algorithms developed by Craig Reynolds. It contains a user interface for interacting with different parameters of the simulation, including the moving policies, number of Boids, view distance and so on. We have targeted the more advanced implementation by doing a 3D version, as well as real-time control of attributes, simulation speed and so on. Spatial hashing and threading has been used to improve performance of the simulation, and in addition to the three basic rules we also have implemented predator and its rule.

## Build instructions

### Linux build

#### Install C++ build tools and compiler
`sudo apt update`   
`sudo apt-get install build-essential gdb`   
`sudo apt install cmake`

#### Install glm, glew, freeglut and wxWidgets
   
`sudo apt install libglew-dev`  
`sudo apt install libglm-dev`  
`sudo apt install freeglut3-dev`   
`sudo apt install libwxgtk3.0-dev`   
`sudo apt install libwxgtk3.0-gtk3-dev`

Install all at once:   
`sudo apt install libglew-dev libglm-dev freeglut3-dev libwxgtk3.0-dev libwxgtk3.0-gtk3-dev`  
#### Clone Boids3D repository
`git clone git@github.com:saviaa1/Boids3D.git`  
`cd Boids3D`

#### Compile Boids3D
`mkdir build`  
`cd build`  
`cmake ..`  
`make`

#### Run Boids3D
`./boid_app`

#### Possible errors and fixes:
OpenGL Error: Install a newer version of OpenGL.  
"The RandR library and headers were not found":  
`sudo apt-get install xorg-dev libglu1-mesa-dev`  


If the app runs, but only draws one triangle and console shows message:  
`Failed to complie vertex
0:1(10): error: GLSL 3.30 is not supported. Supported versions are: 1.10, 1.20, 1.30, 1.40, 1.00 ES, and 3.00 ES`  
`Failed to complie fragment
0:1(10): error: GLSL 3.30 is not supported. Supported versions are: 1.10, 1.20, 1.30, 1.40, 1.00 ES, and 3.00 ES`  
run command:  
`export MESA_GL_VERSION_OVERRIDE=3.10`

### Windows build
#### Download and install Visual Studio 2019 Community
https://visualstudio.microsoft.com/downloads/

#### Download and install git
https://git-scm.com/download/win

#### Download and install cmake
https://cmake.org/download/

#### Download and install vcpkg
https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019

`cd C:\`  
`git clone https://github.com/Microsoft/vcpkg`  
`cd vcpkg`  
`.\bootstrap-vcpkg.bat`

#### Install glm, glew, freeglut and wxWidgets using vcpkg
`.\vcpkg install glm:x64-windows`  
`.\vcpkg install glew:x64-windows`  
`.\vcpkg install freeglut:x64-windows`  
`.\vcpkg install wxwidgets:x64-windows`  
`set VCPKG=C:\vcpkg`

#### Clone Boids3D repository
`cd ..`  
`git clone git@github.com:saviaa1/Boids3D.git`

#### Compile Boids3D
`cd Boids3D`  
`buildboids.bat`

#### Run Boids3D
`cd ReleaseWin64Dynamic`  
`release\boid_app.exe`