cmake_minimum_required(VERSION 3.20)
project(logme_submodule_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- logme as a git submodule ---
# Expected layout:
#   external/logme  (git submodule pointing to https://github.com/efmsoft/logme.git)
# logme static library lives in: external/logme/logme
add_subdirectory(external/logme/logme)

add_executable(example
  src/main.cpp
)

target_link_libraries(example
  PRIVATE
    logme
)

# Enable logging in Release builds
target_compile_definitions(example
  PRIVATE
    LOGME_INRELEASE
)
