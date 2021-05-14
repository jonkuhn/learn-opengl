add_library(Graphics STATIC)
if(MSVC)
  target_compile_options(Graphics PRIVATE /W4 /WX)
else()
  target_compile_options(Graphics PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_sources(Graphics
  PRIVATE
    OpenGL/GlfwException.h
    OpenGL/GlfwException.cpp
    OpenGL/IGlfwWrapper.h
    OpenGL/GlfwWrapper.h
    OpenGL/GlfwWrapper.cpp
    OpenGL/OpenGLHelpers.h
    OpenGL/OpenGLHelpers.cpp
    OpenGL/IOpenGLWrapper.h
    OpenGL/OpenGLWrapper.h
    OpenGL/IShader.h
    OpenGL/Shader.h
    OpenGL/Shader.cpp
    OpenGL/IShaderProgram.h
    OpenGL/ShaderProgram.h
    OpenGL/ShaderProgram.cpp
    OpenGL/ITexture.h
    OpenGL/Texture.h
    OpenGL/Texture.cpp
    OpenGL/TileMap.h
    OpenGL/ITileMapShaderProgram.h
    OpenGL/TileMapShaderProgram.h
    OpenGL/TileMapShaderProgram.cpp
    OpenGL/UniqueHandle.h
    OpenGL/VertexArray.h
    OpenGL/IOpenGLWindow.h
    OpenGL/Window.h
    OpenGL/Window.cpp
    IFactory.h
    IImage.h
    PngImage.h
    PngImage.cpp
    ILibPngWrapper.h
    LibPngWrapper.h
    ITileMap.h
)
target_link_libraries(Graphics ${CONAN_LIBS})
