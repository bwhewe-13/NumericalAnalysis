cmake_minimum_required(VERSION 3.15)
project(numeric)

include(GNUInstallDirs)
include(CTest)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_PYTHON_BINDINGS "Build pybind11 extension module" ON)

if(BUILD_PYTHON_BINDINGS)
    set(Python3_FIND_VIRTUALENV FIRST)
    find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/pybind11/CMakeLists.txt")
        add_subdirectory(third_party/pybind11)
    else()
        if(Python3_Interpreter_FOUND)
            execute_process(
                COMMAND "${Python3_EXECUTABLE}" -c "import pybind11; print(pybind11.get_cmake_dir())"
                RESULT_VARIABLE _pybind11_query_result
                OUTPUT_VARIABLE _pybind11_cmake_dir
                OUTPUT_STRIP_TRAILING_WHITESPACE
                ERROR_QUIET
            )

            if(_pybind11_query_result EQUAL 0 AND _pybind11_cmake_dir)
                get_filename_component(_pybind11_prefix "${_pybind11_cmake_dir}/../../.." ABSOLUTE)
                list(PREPEND CMAKE_PREFIX_PATH "${_pybind11_prefix}")
                set(pybind11_DIR "${_pybind11_cmake_dir}" CACHE PATH "Path to pybind11 CMake config")
            endif()
        endif()

        find_package(pybind11 CONFIG QUIET)
        if(NOT pybind11_FOUND)
            FetchContent_Declare(
                pybind11
                GIT_REPOSITORY https://github.com/pybind/pybind11.git
                GIT_TAG v2.13.6
            )
            FetchContent_MakeAvailable(pybind11)
        endif()
    endif()

    pybind11_add_module(root_approximation
        src/bindings/root_approximation.cpp
        src/root_approximation.cpp
    )

    target_include_directories(root_approximation
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
            ${Python3_INCLUDE_DIRS}
    )

    target_link_libraries(root_approximation PRIVATE Python3::Module)

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
