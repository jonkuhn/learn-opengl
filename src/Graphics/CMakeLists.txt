add_library(Graphics STATIC)
if(MSVC)
  target_compile_options(Graphics PRIVATE /W4 /WX)
else()
  target_compile_options(Graphics PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_sources(Graphics
  PRIVATE
    OpenGL/IGlfwWrapper.h
    OpenGL/GlfwWrapper.h
    OpenGL/GlfwWrapper.cpp
    OpenGL/IOpenGLWrapper.h
    OpenGL/OpenGLWrapper.h
    OpenGL/IShader.h
    OpenGL/Shader.h
    OpenGL/Shader.cpp
    OpenGL/ShaderProgram.h
    OpenGL/ShaderProgram.cpp
)
target_link_libraries(Graphics ${CONAN_LIBS})
