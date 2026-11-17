cmake_minimum_required(VERSION 3.16)

project(SoundBranch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

list(FILTER SOURCES EXCLUDE REGEX "/(build|\\.git)/")

add_executable(program ${SOURCES})

target_include_directories(program PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(program PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra>
)