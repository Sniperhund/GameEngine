# GameEngine

This is my small game engine project. <br>
It's written in C++ and uses bgfx for rendering

It's gonna be cross platform (Atleast Windows and MacOS) <br>
I'm planning on adding Linux support, but I do not have a Linux machine to test it on.

### Build

Hopefully all libraries compiles out of the box. <br>
If you have any issues with building, please let me know.

### Build (Windows)

For now you have to manually symlink Core to the Libs file in Editor/Runtime <br>
After you've done that you need to run:

-   `cmake -B build -S .`
-   `cmake --build build`

This is gonna be updated to use a script for building in the future.

### Build (MacOS/Linux)

This is untested on Linux but should work. <br>

You need to run:

-   `./Setup.sh`
-   `./Build.sh <Editor|Runtime>`
