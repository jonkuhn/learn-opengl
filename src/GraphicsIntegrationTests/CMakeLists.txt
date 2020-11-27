add_executable(GraphicsIntegrationTests)
if(MSVC)
  target_compile_options(GraphicsIntegrationTests PRIVATE /W4 /WX)
else()
  target_compile_options(GraphicsIntegrationTests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_sources(GraphicsIntegrationTests
  PRIVATE
    main_test.cpp
    OpenGL/ShaderTests.cpp
)
target_include_directories(GraphicsIntegrationTests PRIVATE
  ../
)
target_link_libraries(GraphicsIntegrationTests Graphics ${CONAN_LIBS})
