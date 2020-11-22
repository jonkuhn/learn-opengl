# Journal
The intent of this document is to document how my mental model of OpenGL programming evolves as I go through the tutorial and eventually experiment on my own.

## Nov 22, 2020
I want to organize the messy code in main, but I think I need to understand things a bit more before I can organize it.  I think being able to organize it will demonstrate understanding it.

The thoughts/questions I have at this point are:
- Does a VAO end up mapping to a single on-screen entity?
- If so, do you only bind it and draw it when it is on-screen?  I think it may be possible to keep off-screen things in memory and rely on OpenGL's clipping to only draw what is necessary.  I wonder how efficient that is.  I am curious if you would build up an entire level or sub-level of a game in OpenGL and rely on it to only render what is visible.  There will obviously be limits to that approach.  If a level or level section is too large it would take up too much memory, so the program itself must only load a "reasonable" amount.  For a simple 2D sprite-based game it may be possible to.
- There was mention in the tutorial of copying information into GPU memory being expensive.  However, I assume that must be how you update the positions of things in a game.  There was mention of configuring things differently (GL_STREAM_DRAW vs GL_STATIC_DRAW vs GL_DYNAMIC_DRAW) based on how frequently the object is updated so that is probably related.
- Thinking of a 2D side-scroller for example, I am assuming that you would keep things like backgrounds in GPU memory and keep their positions static (and use GL_STATIC_DRAW).  Then for things that move like characters you would use GL_DYNAMIC_DRAW.