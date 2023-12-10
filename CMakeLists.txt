cmake_minimum_required(VERSION 3.12)

project(GSEngine)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)

if(MSVC)
	set(CMAKE_CXX_FLAGS "/W3 /WX- /EHsc")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /NDEBUG")
else()
	set(CMAKE_CXX_FLAGS "-W -Wall -Wno-unused -Wno-sign-compare")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

SET(SOURCES 
    "src/FilesIO/FilesIO.cpp"
    "src/Graphics/Shaders/CircleShaderProgram.cpp"
    "src/Graphics/Shaders/SdfTextShaderProgram.cpp"
    "src/Graphics/Shaders/SpriteShaderProgram.cpp"
    "src/Graphics/Shaders/ShaderProgram.cpp"
    "src/Graphics/Shapes/Sprites/CommonSprite.cpp"
    "src/Graphics/Shapes/Sprites/SDFChar.cpp"
    "src/Graphics/Shapes/Sprites/Sprite.cpp"
    "src/Graphics/Shapes/Circle.cpp"
    "src/Graphics/Shapes/Line.cpp"
    "src/Graphics/Shapes/Model.cpp"
    "src/Graphics/Shapes/Rectangle.cpp"
    "src/Graphics/Text/FontController.cpp"
    "src/Graphics/Text/TextBlock.cpp"
    "src/Graphics/Text/TextFont.cpp"
    "src/Graphics/Text/TextRenderer.cpp"
    "src/Graphics/Textures/PNGLoader.cpp"
    "src/Graphics/Textures/Texture.cpp"
    "src/Graphics/Textures/TexturesController.cpp"
    "src/Graphics/Textures/TGALoader.cpp"
    "src/Graphics/BufferObject.cpp"
    "src/Graphics/Graphics.cpp"
    "src/Graphics/GraphicsResources.cpp"
    "src/GUI/Controlls/Button.cpp"
    "src/GUI/Controlls/Slider.cpp"
    "src/GUI/Application.cpp"
    "src/GUI/Screen.cpp"
    "src/GUI/ScreenController.cpp"
    "src/GUI/Window.cpp"
)

find_package(OpenGL REQUIRED)

SET(LIB_GLEW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3pp/glew)
add_library(glew SHARED IMPORTED)
set_target_properties(glew PROPERTIES IMPORTED_LOCATION ${LIB_GLEW_PATH}/lib-mingw-w64/glew32.dll)
set_target_properties(glew PROPERTIES IMPORTED_IMPLIB ${LIB_GLEW_PATH}/lib-mingw-w64/libglew32.dll.a)
target_include_directories(glew INTERFACE ${LIB_GLEW_PATH}/include)

SET(LIB_GLFW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3pp/glfw3)
add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${LIB_GLFW_PATH}/lib-mingw-w64/glfw3.dll)
set_target_properties(glfw PROPERTIES IMPORTED_IMPLIB ${LIB_GLFW_PATH}/lib-mingw-w64/libglfw3dll.a)
target_include_directories(glfw INTERFACE ${LIB_GLFW_PATH}/include)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC glfw glew OpenGL::GL OpenGL::GLU
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC GLFW_DLL GLFW_INCLUDE_NONE
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy $<TARGET_FILE:glew> $<TARGET_FILE:glfw> ${CMAKE_SOURCE_DIR}/bin
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/bin/data
)
