## Tile Renderer

This is a small tile-based rendering project to learn a bit more about
[OpenGL](https://www.khronos.org/opengl/) and brush up on [C++](https://isocpp.org/).

Tiles are rendered in two stages. The first stage only renders the pixels "uncovered" after moving the viewport.
These are rendered to a framebuffer, the second stage then simply copies the framebuffer to screen.

![Alt text](./diagrams/render_pipeline.svg)

As only "new" pixels are rendered, the framebuffer is not cleared between frames. Instead "new" pixels are
written over those that should no longer appear. The framebuffer is then copied to screen with an offset to
give a complete image.

![Alt text](./diagrams/tile_shader.svg)

### Scaling

The Framebuffer may be smaller than the screen, so the final image will be scaled. As there is no filtering,
this will produce some aliasing for screen sizes that are not integer multiples of the framebuffer.


### Why is this so overly complicated?

Because I wanted an excuse to dig around in OpenGL a bit more. So building a simple 2D renderer and adding in
some extra steps seemed like a good way to utilise a lot of things, particularly framebuffers, buffer textures
and geometry shaders. I've already done a ton of work with linear algebra and coordinate systems as part of my
job, so for this project I just wanted to focus on getting into the OpenGL features.
I also like the aesthetics of old-school pixel art and tile based games, so this seemed like it would be fun.

### What now?

Eventually I would like to animate some of the tiles and be able to render sprites. Ultimately it would be nice
to build a simple top-down shooter, time and other committments permitting...

