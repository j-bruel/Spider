cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

# Include Hunter, a cmake package manager
#set(HUNTER_ROOT "")
include("../../cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.19.111.tar.gz"
        SHA1 "683bdd1a56711abd24907973665f7f58f792ce5f"
)

project(example_client)

hunter_add_package(Boost COMPONENTS program_options system filesystem)
find_package(Boost CONFIG REQUIRED program_options system filesystem)

## Include directory
set(SERVER_INCLUDE include)
include_directories(${SERVER_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES src/main.cpp src/*.cpp
        ../../src/Socket/TcpClientSocket.cpp
        ../../src/Request/Request.cpp
        ../../src/Request/AuthReq.cpp
        ../../src/Json/JsonParser.cpp
        ../../src/Request/RequestManager.cpp
        ../../src/Packet/PacketManager.cpp
        ../../src/Request/PingReq.cpp
        ../../src/Request/PingResp.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.hpp
        ../../include/Socket/TcpClientSocket.hpp
        ../../include/Socket/TcpClientSocket.hpp
        ../../include/Request/Request.hpp
        ../../include/Request/AuthReq.hpp
        ../../include/Packet/Packet.hpp
        ../../include/Json/JsonParser.hpp
        ../../include/Request/RequestManager.hpp
        ../../include/Packet/PacketManager.hpp
        ../../include/Request/PingReq.hpp
        ../../include/Request/PingResp.hpp)

# Source files
set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::system Boost::filesystem Boost::program_options pthread)