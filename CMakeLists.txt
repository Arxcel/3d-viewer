cmake_minimum_required(VERSION 3.10...3.15)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/cpack)
project(viewer3D LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")

add_subdirectory(3rdParty)

find_package(OpenGL 3.0 REQUIRED)

add_subdirectory(src)
add_subdirectory(inc)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# if (APPLE)
# target_compile_options(bomberman PRIVATE -Wall -Wextra -Werror -Wno-deprecated -fvisibility=hidden)
# endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        USE_FOLDERS ON)

target_include_directories(${PROJECT_NAME} PRIVATE inc/)

target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        SDL2::SDL2
        glew::glew
        glm::glm
        )

function(LINK_ASSETS TARGET_ARG SRC_ARG DIST_ARG)
    add_custom_command(TARGET ${TARGET_ARG} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink "${SRC_ARG}/Assets" "${DIST_ARG}/Assets" DEPENDS "${DIST_ARG}")
endfunction()

if (MSVC)
    link_assets(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else ()
    link_assets(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif ()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

