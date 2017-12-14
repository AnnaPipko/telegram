include_directories(.)
include_directories(commons)

set(CXX_STANDARD 17)
if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.2)
    set(CXX_STANDARD 14)
endif()

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
    set(CXX_STANDARD 11)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND APPLE)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
        set(CXX_STANDARD 14)
    else()
        set(CXX_STANDARD 17)
    endif()
endif()

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CXX_STANDARD} -Wall -Wextra -Wpedantic -g")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")
endif()


set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
        CACHE STRING "Compiler flags in asan build"
        FORCE)