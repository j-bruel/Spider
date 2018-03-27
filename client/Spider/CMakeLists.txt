cmake_minimum_required(VERSION 3.5)
project(Spider)

set(PROJECT_NAME Spider)
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

message("Please wait, The spider project is preparing the environnement with untar sources.")
execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf ${CMAKE_CURRENT_SOURCE_DIR}/lib.zip
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/sqlite)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/boost/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/openssl64/include)

set(Boost_USE_STATIC_LIBS        ON)
set(BOOST_LIBRARYDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/boost)
set(BOOST_INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/boost/include)

find_package(Boost COMPONENTS program_options system filesystem date_time regex REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.hpp)

set(SOURCE_FILES    ${SOURCE_FILES}
                    src/sqlite3.c
                    ${INCLUDE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}    ${Boost_LIBRARIES}
                                ${CMAKE_CURRENT_SOURCE_DIR}/lib/openssl64/release/libeay32.lib
                                ${CMAKE_CURRENT_SOURCE_DIR}/lib/openssl64/release/ssleay32.lib)