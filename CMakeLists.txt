cmake_minimum_required(VERSION 3.15)
project(ChessRTS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/Board
    ${CMAKE_SOURCE_DIR}/Entities
    ${CMAKE_SOURCE_DIR}/Core
    ${CMAKE_SOURCE_DIR}/Renderer
    ${CMAKE_SOURCE_DIR}/Systems
)

file(GLOB_RECURSE SOURCES
    "Core/*.cpp"
    "Board/*.cpp"
    "Renderer/*.cpp"
    "Systems/*.cpp"
)

add_executable(ChessRTS ${SOURCES})
