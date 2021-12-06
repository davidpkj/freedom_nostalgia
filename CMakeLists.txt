cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
add_definitions(-std=c++17) 
project(freedom_nostalgia)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
        FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 0851960397f02a477d80eda2239f90fae14dec64
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# raylib-cpp
find_package(raylib-cpp QUIET)
if (NOT raylib-cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib-cpp
        URL https://github.com/RobLoach/raylib-cpp/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib-cpp)
    if (NOT raylib-cpp_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib-cpp)
        set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING             OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib-cpp_SOURCE_DIR} ${raylib-cpp_BINARY_DIR})
    endif()
endif()

# tmx
find_package(tmx QUIET)
if (NOT tmx_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        tmx
        URL https://github.com/baylej/tmx/archive/master.tar.gz
    )
    FetchContent_GetProperties(tmx)
    if (NOT tmx_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(tmx)
        add_subdirectory(${tmx_SOURCE_DIR} ${tmx_BINARY_DIR})
    endif()
endif()

# boost
set(BOOST_INCLUDEDIR /usr/include/boost)
set(BOOST_LIBRARYDIR /usr/lib/boost)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

find_package(
    Boost 
    1.75.0
    COMPONENTS thread
    system
    log
    log_setup
    program_options
    REQUIRED
)

include_directories(${Boost_INCLUDE_DIRS})

set(raylib_VERBOSE 1)
set(PROJECT_SOURCES "src/main.cpp")
set(PROJECT_NAME "Freedom_Nostalgia")
set(
    PROJECT_UTIL 
    "src/util/vector.cpp"
    "src/util/log.cpp"
    "src/classes/character.cpp"
    "src/classes/player.cpp"
    "src/handlers/control.cpp"
    "src/handlers/texture.cpp"
    "src/handlers/map.cpp"
)
add_executable(${PROJECT_NAME} ${PROJECT_UTIL} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib-cpp tmx ${Boost_LIBRARIES})
