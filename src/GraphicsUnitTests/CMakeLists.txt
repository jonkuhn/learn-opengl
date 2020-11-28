add_executable(GraphicsUnitTests)
if(MSVC)
  target_compile_options(GraphicsUnitTests PRIVATE /W4 /WX)
else()
  target_compile_options(GraphicsUnitTests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_sources(GraphicsUnitTests
  PRIVATE
    main_test.cpp
    OpenGL/MockOpenGLWrapper.h
    OpenGL/ShaderTests.cpp
)
target_include_directories(GraphicsUnitTests PRIVATE
  ../
)
target_link_libraries(GraphicsUnitTests Graphics ${CONAN_LIBS})
