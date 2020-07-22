# C++ 3D Boids

## Build instructions

### Run these commands in the root of the project:

`mkdir build`  
`cd build`  
`cmake ..`  
`make`

For the app to run, _ColorFragmentShader.fragmentshader_ and _TransformVertexShader.vertexshader_ need to be moved to /build.  
This can be done by the `mv` command.

After this, run the application with: `./boid_app`

### Possible errors and fixes:

OpenGL Error: Install a newer version of OpenGL.  
"The RandR library and headers were not found": `sudo apt-get install xorg-dev libglu1-mesa-dev`
