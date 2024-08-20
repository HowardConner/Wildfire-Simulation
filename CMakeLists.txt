cmake_minimum_required(VERSION 3.10)

# Project name
project(MainProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(/usr/include/raylib)

# Source files
set(SOURCES
    main.cpp # Add your main source file here
    RenderEngine.cpp
    game.cpp
    lib/Vec2f.cpp
    lib/Vec2i.cpp
)

# Executable name
set(EXECUTABLE_NAME MAIN)

# Add executable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} raylib GL m pthread dl rt X11)

# Ensure raygui.h is available in the source directory
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src/raygui.h")
    message(FATAL_ERROR "raygui.h not found in src directory. Please place raygui.h in the src directory.")
endif()

# Custom commands to handle the raygui compilation
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/src/raygui.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/raygui.h ${CMAKE_SOURCE_DIR}/src/raygui.c
    DEPENDS ${CMAKE_SOURCE_DIR}/src/raygui.h
    COMMENT "Renaming raygui.h to raygui.c"
)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/raygui.so
    COMMAND gcc -o ${CMAKE_BINARY_DIR}/raygui.so ${CMAKE_SOURCE_DIR}/src/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    DEPENDS ${CMAKE_SOURCE_DIR}/src/raygui.c
    COMMENT "Compiling raygui.c to create raygui.so"
)

add_custom_target(raygui ALL DEPENDS ${CMAKE_BINARY_DIR}/raygui.so)

# Custom commands for cleaning and running
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove ${EXECUTABLE_NAME} ${CMAKE_BINARY_DIR}/raygui.so
)

add_custom_target(run_all
    COMMAND ${EXECUTABLE_NAME}
    DEPENDS ${EXECUTABLE_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
