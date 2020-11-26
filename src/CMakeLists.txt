add_subdirectory(Graphics)
if(BUILD_TESTING)
  add_subdirectory(GraphicsUnitTests)
endif()
add_executable(learn-opengl)
target_sources(learn-opengl
  PRIVATE
    main.cpp
)
if(MSVC)
  target_compile_options(learn-opengl PRIVATE /W4 /WX)
else()
  target_compile_options(learn-opengl PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
target_link_libraries(learn-opengl Graphics ${CONAN_LIBS})
