cmake_minimum_required(VERSION 3.16)
project(logme_submodule_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Example-level options
set(LOGME_LINKAGE "STATIC" CACHE STRING "How to link logme: STATIC or SHARED")
set_property(CACHE LOGME_LINKAGE PROPERTY STRINGS STATIC SHARED)

set(USE_ALLSTAT OFF CACHE BOOL "Use AllStat library")
set(USE_JSONCPP OFF CACHE BOOL "Use JSONCPP library")

# -------

set(LOGME_BUILD_EXAMPLES OFF CACHE BOOL "")
set(LOGME_BUILD_TESTS OFF CACHE BOOL "")

if (LOGME_LINKAGE STREQUAL "STATIC")
  set(LOGME_BUILD_DYNAMIC OFF CACHE BOOL "")
  set(LOGME_BUILD_STATIC ON CACHE BOOL "")
elseif (LOGME_LINKAGE STREQUAL "SHARED")
  set(LOGME_BUILD_DYNAMIC ON CACHE BOOL "")
  set(LOGME_BUILD_STATIC OFF CACHE BOOL "")
else()
  message(FATAL_ERROR "LOGME_LINKAGE must be STATIC or SHARED (got: ${LOGME_LINKAGE})")
endif()

if(USE_ALLSTAT)
  if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/allstat/cmake/Findallstat.cmake)
    message(FATAL_ERROR "USE_ALLSTAT=ON but external/allstat is missing. Run: git submodule update --init --recursive (or disable USE_ALLSTAT).")
  endif()

  list(APPEND CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/external/allstat/cmake) 
  find_package(allstat MODULE)

  include_directories(${CMAKE_SOURCE_DIR}/external/allstat/AllStat/include)
  add_definitions(-DUSE_ALLSTAT)
endif()

if(USE_JSONCPP)
  if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/jsoncpp/CMakeLists.txt)
    message(FATAL_ERROR "USE_JSONCPP=ON but external/jsoncpp is missing. Run: git submodule update --init --recursive (or disable USE_JSONCPP).")
  endif()

  set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
  set(BUILD_OBJECT_LIBS OFF CACHE BOOL "" FORCE)
  set(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
  set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)
  set(JSONCPP_WITH_WARNING_AS_ERROR OFF CACHE BOOL "" FORCE)

  add_subdirectory(external/jsoncpp)
  add_definitions(-DUSE_JSONCPP)
endif()

add_subdirectory(external/logme)
add_executable(example src/main.cpp)

target_include_directories(example PRIVATE external/logme/logme/include)

if (WIN32)
  target_link_libraries(example PRIVATE Ws2_32)
endif()

# Enable logging in Release builds
target_compile_definitions(example PRIVATE
  LOGME_INRELEASE
)

# Keep compatibility with logme headers/build logic
if (LOGME_LINKAGE STREQUAL "STATIC")
  target_compile_definitions(example PRIVATE _LOGME_STATIC_BUILD_)
  target_link_libraries(example PRIVATE logme)
else()
  target_link_libraries(example PRIVATE logmed)
endif()

if(USE_ALLSTAT)
  target_link_libraries(example PRIVATE ${ALLSTAT_LIBRARIES})
endif()

if (USE_JSONCPP)
  if (TARGET JsonCpp::JsonCpp)
    set(JsoncppTarget JsonCpp::JsonCpp)
  elseif (TARGET jsoncpp_lib)
    set(JsoncppTarget jsoncpp_lib)
  elseif (TARGET jsoncpp_static)
    set(JsoncppTarget jsoncpp_static)
  else()
    message(FATAL_ERROR "USE_JSONCPP=ON but no jsoncpp target was created.")
  endif()

  if (TARGET logme)
    target_link_libraries(logme PUBLIC ${JsoncppTarget})
  endif()

  if (TARGET logmed)
    target_link_libraries(logmed PUBLIC ${JsoncppTarget})
  endif()

  target_link_libraries(example PUBLIC ${JsoncppTarget})
endif()
