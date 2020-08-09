# C++ 3D Boids

## Build instructions

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
