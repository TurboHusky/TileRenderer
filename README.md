## Tile Renderer

This is a small project, started with the aim of learning a bit more about [C++](https://isocpp.org/) and [OpenGL](https://www.khronos.org/opengl/).

The idea is to implement a simple tile-based renderer, and perhaps do something more interesting with it later on. At the moment the project is very minimal, it's an early version for learning purposes more than anything else,  so there is no support beyond what is currently uploaded.

Current goals:
- Encapsulate OpenGL code with RAII
- Try and run as much code as possible on the GPU
- Keep interfaces simple

At present the renderer is in a working state, however it does next to nothing and still needs tidying up. Encapsulation isn't quite there, magic numbers abound and initialisers are still quite messy. Once that's done I'll think about expanding the scope.

For anyone interested in learning more, ["Learn OpenGL"](https://learnopengl.com/) does a good job of explaining OpenGL fundamentals.