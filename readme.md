# GameEngine

This is my small game engine project. <br>
It's written in C++ and uses bgfx for rendering

It's gonna be cross platform (Atleast Windows and MacOS) <br>
I'm planning on adding Linux support, but I do not have a Linux machine to test it on.

### Build

Hopefully all libraries compiles out of the box. <br>
If you have any issues with building, please let me know.

### Build (Windows)

You need to run:

-   `cmake -B build -S .`
-   `cmake --build build`

After that you should have a `Editor` folder and `Runtime` folder in the `build` folder. <br>

This is gonna be updated to use a script for building in the future.

### Build (MacOS/Linux)

This is untested on Linux but should work. <br>

You need to run:

-   `./Build.sh <Editor|Runtime>`

### Build (CLion)

For easier development, you can use CLion instead of the Build script