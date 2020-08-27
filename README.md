# C++ 3D Boids

## Build instructions

### Linux build 
### Run these commands in the root of the project:

`mkdir build`  
`cd build`  
`cmake ..`  
`make`

For the app to run, boid.shader need to be moved  
from /src to /build.

After this, run the application with: `./boid_app`

### Possible errors and fixes:

OpenGL Error: Install a newer version of OpenGL.  
"The RandR library and headers were not found": `sudo apt-get install xorg-dev libglu1-mesa-dev`  
If the app runs, but only draws one white boid with a blue background, run this command : `export MESA_GL_VERSION_OVERRIDE=3.10`

### 3D libs added
`sudo apt install libglew-dev`  
`sudo apt install libglm-dev` // opengl Math library

### Windows build (powershell.exe needs to be in path)
1. Download and install git
https://git-scm.com/download/win

2. Download and install cmake
https://cmake.org/download/

2. Download and install vcpkg
(https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019)

`cd C:\`
`git clone https://github.com/Microsoft/vcpkg`
`cd vcpkg`
`.\bootstrap-vcpkg.bat`

3. Install glm, glew, freeglut and wxWidgets using vcpkg

`.\vcpkg install glm:x64-windows`
`.\vcpkg install glew:x64-windows`
`.\vcpkg install freeglut:x64-windows`
`.\vcpkg install wxwidgets:x64-windows`
`set VCPKG=C:\vcpkg`

4. Clone Boids3D repository

`cd ..`
`git clone git@github.com:saviaa1/Boids3D.git`

5. Compile Boids3d

`cd Boids3D`
`buildboids.bat`

6. Run Boids3D

`cd ReleaseWin64Dynamic`
`release\boid_app.exe`