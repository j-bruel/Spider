cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

# Include Hunter, a cmake package manager
#set(HUNTER_ROOT "")
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.19.111.tar.gz"
        SHA1 "683bdd1a56711abd24907973665f7f58f792ce5f"
)

project(example_client)

hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost CONFIG REQUIRED system filesystem)

## Include directory
set(SERVER_INCLUDE include)
include_directories(${SERVER_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.hpp)

# Source files
set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::system Boost::filesystem pthread ws2_32)
    else()
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::system Boost::filesystem pthread)
endif (WIN32)