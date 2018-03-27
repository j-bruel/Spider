cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

#include(ExternalProject)
#include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Include Hunter, a cmake package manager
#set(HUNTER_ROOT "")
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.19.111.tar.gz"
        SHA1 "683bdd1a56711abd24907973665f7f58f792ce5f"
)

project(server)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# Boost
hunter_add_package(Boost COMPONENTS program_options system filesystem)
find_package(Boost CONFIG REQUIRED program_options system filesystem)

# OpenSSL
hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

## Include directory
set(SERVER_INCLUDE include)
include_directories(${SERVER_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES src/Db/sqlite3.c src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/Db/sqlite3.h include/*.hpp)

# Source files
set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDE_FILES})

add_subdirectory(example/client)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC
        Boost::system
        Boost::filesystem
        Boost::program_options
        pthread
        OpenSSL::SSL
        OpenSSL::Crypto)