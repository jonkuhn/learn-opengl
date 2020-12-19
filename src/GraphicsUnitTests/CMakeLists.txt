add_executable(GraphicsUnitTests)
if(MSVC)
  target_compile_options(GraphicsUnitTests PRIVATE /W4 /WX)
else()
  target_compile_options(GraphicsUnitTests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_sources(GraphicsUnitTests
  PRIVATE
    main_test.cpp
    ImageTests.cpp
    TestHelpers.h
    OpenGL/MockGlfwWrapper.h
    OpenGL/MockOpenGLWrapper.h
    OpenGL/MockShader.h
    OpenGL/ShaderProgramTests.cpp
    OpenGL/ShaderTests.cpp
    OpenGL/WindowTests.cpp
    MockLibPngWrapper.h
)
target_include_directories(GraphicsUnitTests PRIVATE
  ../
)
target_link_libraries(GraphicsUnitTests Graphics ${CONAN_LIBS})
