# Set cmake version, project name and project version
cmake_minimum_required(VERSION 3.13...3.23)

project(
      RustyCoin 
      VERSION 1.0.0 
      DESCRIPTION "A basic proof-of-stake based cryptocurrency implementation in C++"
      LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

      # Ensure -std=c++xx instead of -std=g++xx
      set(CMAKE_CXX_EXTENSIONS OFF)

      # Support folders in IDEs
      set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()


add_library(
      net
      src/net/sockets/Socket.hpp
      src/net/sockets/Socket.cpp

      src/net/common/Endpoint.hpp
      src/net/common/Endpoint.cpp
      src/net/common/IPVersion.hpp
      src/net/common/lib_includes.hpp
      src/net/common/NetConstants.hpp      
)

target_include_directories(
      net PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/src/net
)

# Link to Winsock if the host is on Windows
if(WIN32)
      target_link_libraries(
            net
            wsock32 
            ws2_32
      )
endif()

add_executable(
      RustyCoin 
      main.cpp
)

target_link_libraries(RustyCoin net)

find_package(OpenSSL REQUIRED)