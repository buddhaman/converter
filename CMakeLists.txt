cmake_minimum_required(VERSION 3.21)

project(convert)

add_executable(converter src/main.cpp)

target_include_directories(converter PRIVATE include)

# Emscripten specific settings
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX .js)
    
    # Uncomment the option you want to use:
    # Increase initial memory
    # set_target_properties(converter PROPERTIES LINK_FLAGS "-s INITIAL_MEMORY=32MB")
    
    # Allow memory growth
    set_target_properties(converter PROPERTIES LINK_FLAGS "-s ALLOW_MEMORY_GROWTH=1")
endif()
