# Journal
The intent of this document is to document how my mental model of OpenGL programming evolves as I go through the tutorial (https://learnopengl.com) and eventually experiment on my own.

## Nov 30, 2020
Wrote unit and integration tests for Window.  Currently they don't cover the framebuffer resize callback.  I am thinking that would be best to cover with an integration test that calls glfwSetWindowSize and then (after an update call) does a glGet call for the viewport.  This would require adding SetWindowSize to IGlfwWrapper and Window.  Probably not necessary for moving on, but I may do it.

Next I can move on to wrapping the VBO, VAO and EBO OpenGL objects.

I think a good initial higher level goal may be to have a higher level (non-OpenGL specific) 2D sprite class that is injected with some interface that happens to be implemented by OpenGL.

the other higher level goal would be to follow the tutorial more exactly and build up proper C++ classes around everything necessary to make each of the future things work.  However, with just a sprite class I can play around with a lot of 2D graphics and game ideas.  Not that I have any great game design ideas.

I guess it just depends on what I feel like doing and learning about the most.

## Nov 28, 2020
Wrote unit and integration tests for ShaderProgram.  Next up is likely to build the Window class, unless I want to put that cleanup off to dig into OpenGL a bit more.  I've read ahead in the tutorial as mentioned previously, but I want to build a good foundation using SOLID design prinicples and unit testing so that issues will be easy to find as things get more complex.  In any case it was a good refresher on how to do these things in C++.

## Nov 27, 2020
I created the GLFW/GLAD wrapper and moved the not-yet-organized initialization code there for now.  Next up is probably to write unit and integration tests for ShaderProgram, then to build the Window class.

## Nov 26, 2020
Wrote Shader integration tests and in doing so I learned about glad depending on a glfw window being set to the current context.  My understanding is that this is due to GLFEW tying the context to the window.  The GLFW documentation mentiones that the only way to do off-screen rendering with it is through hidden windows.  Perhaps there are other ways to do offscreen rendering.  However, I don't really care about offscreen rendering anyway.

I moved some code from main.cpp into a function in OpenGLWrapper and I am temporarily calling it from main.cpp and the integration tests main_test.cpp.  I need to build this code into a window class.  The window class will probably depend on a different library wrapper for GLFW and GLAD.  The window class will take all responsibilities for window related things.  The interface it implements will probably have methods for things like geting input and "Window should close".  It will also probably have a method that sets it as the current context.  The existing OpenGLWrapper should maybe be renamed to something related to OpenGL since there will be more wrappers.  I am also trying to work out how the dependency of the (existing) Library Wrapper on GLFW having set a current context and GLAD having done the loading should be expressed in the code.  It is difficult due to the global nature of these contexts.  It could depend on the window and call a function on it to set the context current and do the loading.  However, it should likey not do that for every call, becuase we won't really have multiple windows.  Maybe this is one of the rare circumstances where the singleton pattern actually makes sense to make sure there is exactly one window and exactly one (OpenGL) OpenGLWrapper because that is a reasonable limitation to have.  I'll have to think about how that impacts testing though.  It would be nice for unit tests for it to be possible to instantiate all the classes by themselves.  The OpenGLWrapper won't be unit tested but the Window class probably should be.

Just had a thought on expressing the OpenGLWrapper depenency on the Window.  Maybe it accepts an interface that can get and set the current context and throws if the current context is not 0 (assuming this means unset), then it sets the context.  Or maybe it just calls a function to set the context and the function to set it just throws if the current value is not 0 or already equal to the one being set.  This seems like a reasonable way to enforce the one window constraint.

## Nov 25, 2020
Finished writing up wrapper classes for OpenGL shaders and shader programs.  I converted the code from the tutorial to use RAII and to have cleaner error handling (such as querying for the info log size and then using std::vector to make a buffer for it.)

I decided to start building up namespaces how I would if this project grows.  The Graphics namespace will hold all graphics code.  At the top level would be abstractions that are independent of OpenGL.  The OpenGL folder will have OpenGL-specific code.  I decided to have namespaces follow folder structure.

I set up CMake to build the Graphics folder as a static library.  I briefly tried playing with making it a shared library, but I had some RPATH troubles on Mac that I didn't feel like solving just now.  It doesn't even need to be any kind of library for the current state of things here anyway.  I think one of the advantages of making it a shared library would be to limit the visibility of some types inside (assuming Mac and Linux support visibility settings similar to Windows declspec stuff).  I think I remember that there are some settings like that.  This page may be useful if I do that:  https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html.  I suppose that the visibility can mostly be achieved by separate public header files as well.  With either method you need to give calling code header files anyway and without a bunch of extra work like pImpl pattern, you need to include the private sections of classes in there anyway.  So definitely not worth it especially for a project where I am just playing around.

However, I clearly enjoy playing with the idea of this growing into something larger (whether it does or not) and thinking about the tools and techniques I would use to set up a larger C++ project.

Next I will probably play with integration and unit testing of Shader and ShaderProgram to get a unit testing framework set up.  I am trying to decide if full unit testing makes sense by using some technique like linking to spy OpenGL functions or injecting the OpenGL implementation via a template argument so it can be swapped for testing.  Integration testing can cover most things a lot better since these are very thin classes.  The only thing I can think of that isn't covered by integration testing would be testing that the delete functions are called by the destructors.  If I use the template approach it will mean the implementation of these classes would need included wherever it is used (due to how templates work), so I'll have to think about that.  I suppose I could do normal constructor injection via an interface like I would in a business software project.  I am not sure how much the overhead would matter.  It definitely wouldn't matter in the I/O-bound projects I am used to, and probably wouldn't matter much here.  Probably best to avoid premature optimization.

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