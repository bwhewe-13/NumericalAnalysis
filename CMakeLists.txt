cmake_minimum_required(VERSION 3.15)
project(numeric)

include(GNUInstallDirs)
include(CTest)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_PYTHON_BINDINGS "Build pybind11 extension module" ON)

if(BUILD_PYTHON_BINDINGS)
    find_package(pybind11 REQUIRED)

    pybind11_add_module(root_approximation
        src/bindings/root_approximation.cpp
        src/root_approximation.cpp
    )

    target_include_directories(root_approximation
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    install(TARGETS root_approximation DESTINATION numeric)
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(BUILD_TESTING)
    find_package(Catch2 3 QUIET CONFIG)
    if(NOT Catch2_FOUND)
        FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.6.0
        )
        FetchContent_MakeAvailable(Catch2)
    endif()

    add_executable(test_root_approximation_cpp
        tests/test_root_approximation.cpp
        src/root_approximation.cpp
    )

    target_include_directories(test_root_approximation_cpp
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(test_root_approximation_cpp
        PRIVATE
            Catch2::Catch2WithMain
    )

    include(Catch)
    catch_discover_tests(test_root_approximation_cpp)
endif()