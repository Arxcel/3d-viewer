find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/glew/CMakeLists.txt")
    message(FATAL_ERROR "glew submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/sdl2/CMakeLists.txt")
    message(FATAL_ERROR "sdl2 submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/3rdParty/glm/CMakeLists.txt")
    message(FATAL_ERROR "glm submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


set( BUILD_SHARED_LIBS OFF CACHE BOOL "Build only static libs" )

## SDL2
set( SDL_STATIC ON CACHE BOOL "Build the static SDL library" )
set( SDL_SHARED OFF CACHE BOOL "Build the shared SDL library" )
add_subdirectory( sdl2 )
add_library(SDL2::SDL2 ALIAS SDL2-static)

## GLEW
if ( WIN32 )
    set( glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library" )
    set( glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library" )
else()
    set( glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library" )
    set( glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library" )
endif()
set( glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL "Build the single context glew library" )
set( glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Build the multi context glew library" )

add_subdirectory( glew )
if ( WIN32 )
    add_library(glew::glew ALIAS libglew_shared)
else()
    add_library(glew::glew ALIAS libglew_static)
endif() 

## glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm/)
add_library(glm::glm ALIAS glm)
