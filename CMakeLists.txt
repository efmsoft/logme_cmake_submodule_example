cmake_minimum_required(VERSION 3.16)
project(logme_submodule_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- logme as a git submodule ---
# Expected layout:
#   external/logme  (git submodule pointing to https://github.com/efmsoft/logme.git)
# logme static library lives in: external/logme/logme
add_subdirectory(external/logme/logme)

target_compile_definitions(logme
  PRIVATE
    LOGME_DISABLE_STD_FORMAT
)

add_executable(example
  src/main.cpp
)

target_compile_definitions(example PRIVATE LOGME_DISABLE_STD_FORMAT)

target_include_directories(example
  PRIVATE
    external/logme/logme/include
)

target_link_libraries(example
  PRIVATE
    logme
)

if (WIN32)
  target_link_libraries(example
    PRIVATE
      Ws2_32
  )
endif()

# Enable logging in Release builds
target_compile_definitions(example
  PRIVATE
    LOGME_INRELEASE
	_LOGME_STATIC_BUILD_
)
