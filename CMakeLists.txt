cmake_minimum_required(VERSION 3.21)
project(test)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
set(CXXFLAGS  "-O3 -s")


add_executable(install_bodyplans scripts/install_bodyplans.cpp manager/source/common.hpp
        manager/source/FileManager.cpp manager/source/FileManager.hpp
        manager/source/GlobalConfigManager.cpp manager/source/GlobalConfigManager.hpp
        manager/source/LocalConfigManager.cpp manager/source/LocalConfigManager.hpp
        manager/source/SteamManager.cpp manager/source/SteamManager.hpp
        manager/third_party/json.hpp manager/third_party/vdf_parser.hpp)

add_executable(uninstall_bodyplans scripts/uninstall_bodyplans.cpp manager/source/common.hpp
        manager/source/FileManager.cpp manager/source/FileManager.hpp
        manager/source/GlobalConfigManager.cpp manager/source/GlobalConfigManager.hpp
        manager/source/LocalConfigManager.cpp manager/source/LocalConfigManager.hpp
        manager/source/SteamManager.cpp manager/source/SteamManager.hpp
        manager/third_party/json.hpp manager/third_party/vdf_parser.hpp)

add_executable(test scripts/test.cpp manager/source/common.hpp
        manager/source/FileManager.cpp manager/source/FileManager.hpp
        manager/source/GlobalConfigManager.cpp manager/source/GlobalConfigManager.hpp
        manager/source/LocalConfigManager.cpp manager/source/LocalConfigManager.hpp
        manager/source/SteamManager.cpp manager/source/SteamManager.hpp
        manager/third_party/json.hpp manager/third_party/vdf_parser.hpp)

add_compile_definitions(LOCAL)