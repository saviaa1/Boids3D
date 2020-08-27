# C++ 3D Boids

## Build instructions

### Linux build

#### Install glm, glew, freeglut and wxWidgets
`sudo apt install libglew-dev`  
`sudo apt install libglm-dev`

#### Clone Boids3D repository
`git clone git@github.com:saviaa1/Boids3D.git`  
`cd Boids3D`

#### Compile Boids3d
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
If the app runs, but only draws one white boid with a blue background, run this command:  
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

#### Compile Boids3d
`cd Boids3D`  
`buildboids.bat`

#### Run Boids3D
`cd ReleaseWin64Dynamic`  
`release\boid_app.exe`