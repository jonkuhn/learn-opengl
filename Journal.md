# Journal
The intent of this document is to document how my mental model of OpenGL programming evolves as I go through the tutorial (https://learnopengl.com) and eventually experiment on my own.

## Nov 22, 2020
After reading up through the "Textures" section of the tutorial I have a better understanding of things and answers to some of my questions.  I also read the opening lines of the next section "Transformations".  Then after writing most of the points below I skimmed the rest of the "Getting Started" section and a bit of the "Lighting" section.
- "Uniforms" can be used to pass information from the main program to the shaders
- Colors can be set on verticies and OpenGL will interpolate the colors between the vertices.
- Texture mapping works similarly where you identify the point in the texture that cooresponds to a particular vertex.
- Skimming over the Transformations chapter it seems like transformation matrices are passed as uniforms to shaders in order to move objects.
- Since the tutorial creates a Shader class I will likely want to build my own class(es) for loading, compiling, linking and passing uniforms to shaders.
- My own class(es) representing textures is likely a good ideas as well.
- For testing code that interacts with OpenGL I may build a separate executable that links against a simple test spy implementations of the OpenGL functions.  I will have to think about if there is value in this or not though.
- Integration testing would be possible for some things that interact with OpenGL (handling of success and failure cases for shader compilation for example.)
- Skimming the discussions of coordinate systems is interesting and leads me to believe that you do build up all of the objects for a level or section of a level in OpenGL with world space coordinates by using the "model" transformation matrix.  Then the view and projection matrices are used by the vertex shader to transform those world coordinates into normalized device coordinates.
- I'll probably start by building some abstractions and then building some 2D world to get going with this first.

## Nov 22, 2020
I want to organize the messy code in main, but I think I need to understand things a bit more before I can organize it.  I think being able to organize it will demonstrate understanding it.

The thoughts/questions I have at this point are:
- Does a VAO end up mapping to a single on-screen entity?
- If so, do you only bind it and draw it when it is on-screen?  I think it may be possible to keep off-screen things in memory and rely on OpenGL's clipping to only draw what is necessary.  I wonder how efficient that is.  I am curious if you would build up an entire level or sub-level of a game in OpenGL and rely on it to only render what is visible.  There will obviously be limits to that approach.  If a level or level section is too large it would take up too much memory, so the program itself must only load a "reasonable" amount.  For a simple 2D sprite-based game it may be possible to.
- There was mention in the tutorial of copying information into GPU memory being expensive.  However, I assume that must be how you update the positions of things in a game.  There was mention of configuring things differently (GL_STREAM_DRAW vs GL_STATIC_DRAW vs GL_DYNAMIC_DRAW) based on how frequently the object is updated so that is probably related.
- Thinking of a 2D side-scroller for example, I am assuming that you would keep things like backgrounds in GPU memory and keep their positions static (and use GL_STATIC_DRAW).  Then for things that move like characters you would use GL_DYNAMIC_DRAW.