cmake_minimum_required(VERSION 3.16)
project(logme_submodule_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LOGME_BUILD_EXAMPLES OFF CACHE BOOL "")
set(LOGME_BUILD_TESTS OFF CACHE BOOL "")
set(LOGME_BUILD_DYNAMIC OFF CACHE BOOL "")
set(LOGME_BUILD_STATIC ON CACHE BOOL "")
add_subdirectory(external/logme)

add_executable(example src/main.cpp)

target_include_directories(example PRIVATE external/logme/logme/include)
target_link_libraries(example PRIVATE logme)

if (WIN32)
  target_link_libraries(example PRIVATE Ws2_32)
endif()

# Enable logging in Release builds
target_compile_definitions(example PRIVATE
  LOGME_INRELEASE
	_LOGME_STATIC_BUILD_
)
