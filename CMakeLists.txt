cmake_minimum_required(VERSION 3.5)

project(GSEngine)

set (CMAKE_CXX_STANDARD 17)

if(MSVC)
	set(CMAKE_CXX_FLAGS "/W3 /WX- /EHsc")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /NDEBUG")
else()
	set(CMAKE_CXX_FLAGS "-W -Wall -Werror -Wno-unused -Wno-sign-compare")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

find_package(OpenGL REQUIRED)

add_definitions(-DGLFW_DLL -DGLFW_INCLUDE_NONE)

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
    PUBLIC ${OPENGL_INCLUDE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC glfw
	PUBLIC glew
	PUBLIC ${OPENGL_gl_LIBRARY}
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy $<TARGET_FILE:glew> $<TARGET_FILE:glfw> ${CMAKE_SOURCE_DIR}/bin
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/data
)
