message("Building started.")
message("Setting project name and version...")

# Set cmake version, project name and project version
cmake_minimum_required(VERSION 3.13...3.23)

project(
      RustyCoin 
      VERSION 1.0.0 
      DESCRIPTION "A basic proof-of-stake based cryptocurrency implementation in C++"
      LANGUAGES CXX)

message("Project name and version set.")
message("Setting CXX standard and ensuring IDE project support...")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

      # Ensure -std=c++xx instead of -std=g++xx
      set(CMAKE_CXX_EXTENSIONS OFF)

      # Support folders in IDEs
      set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()

message("Building string library...")

add_library(
      RustyString
      src/util/string/RustyString.hpp
)

target_include_directories(
      RustyString PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/src/util
)

set_target_properties(RustyString PROPERTIES LINKER_LANGUAGE CXX) # To solve a strange error

message("Building network library...")

add_library(
      net
      src/net/sockets/Socket.hpp
      src/net/sockets/Socket.cpp

      src/net/common/Endpoint.hpp
      src/net/common/Endpoint.cpp
      src/net/common/IPVersion.hpp
      src/net/common/lib_includes.hpp
      src/net/common/NetConstants.hpp
      src/net/common/SocketOptions.hpp
      src/net/common/NetError.hpp
      src/net/common/NetTypes.hpp

      src/net/common/packet/Packet.hpp
      src/net/common/packet/Packet.cpp
      src/net/common/packet/PacketException.hpp
      src/net/common/packet/PacketType.hpp
)

target_include_directories(
      net PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link to Winsock if the host is on Windows
if(WIN32)
      message("Linking with Winsocket...")

      target_link_libraries(
            net
            wsock32 
            ws2_32
      )
endif()

message("Adding executable...")

add_executable(
      RustyCoin 
      main.cpp
)

message("Linking libraries...")

target_link_libraries(RustyCoin net RustyString)

find_package(OpenSSL REQUIRED)

message("Finished building RustyCoin.")