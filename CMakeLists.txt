cmake_minimum_required(VERSION 3.21)
project(test)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
set(CXXFLAGS  "-O3 -s")

add_executable(install_bodyplans source/scripts/install_bodyplans.cpp
        source/includes/FileManager.cpp source/includes/FileManager.hpp
        source/includes/SteamManager.cpp source/includes/SteamManager.hpp
        source/includes/GlobalConfigManager.cpp source/includes/GlobalConfigManager.hpp
        source/includes/LocalConfigManager.cpp source/includes/LocalConfigManager.hpp source/includes/common.hpp)

add_executable(uninstall_bodyplans source/scripts/uninstall_bodyplans.cpp
        source/includes/FileManager.cpp source/includes/FileManager.hpp
        source/includes/SteamManager.cpp source/includes/SteamManager.hpp
        source/includes/GlobalConfigManager.cpp source/includes/GlobalConfigManager.hpp
        source/includes/LocalConfigManager.cpp source/includes/LocalConfigManager.hpp source/includes/common.hpp)

add_executable(test source/scripts/test.cpp
        source/includes/FileManager.cpp source/includes/FileManager.hpp
        source/includes/SteamManager.cpp source/includes/SteamManager.hpp
        source/includes/GlobalConfigManager.cpp source/includes/GlobalConfigManager.hpp
        source/includes/LocalConfigManager.cpp source/includes/LocalConfigManager.hpp source/scripts/test.cpp)

add_compile_definitions(LOCAL)