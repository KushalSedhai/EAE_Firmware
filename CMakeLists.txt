cmake_minimum_required(VERSION 3.16)

project(EAE_Firmware C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Main firmware executable
add_executable(eae_firmware
    src/main.c
    src/can_sim.c
    src/cooling_control.c
    src/fault_manager.c
    src/pid.c
    src/state_machine.c
)

# Header files are stored here
target_include_directories(eae_firmware PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# --------------------------------------------------
# GoogleTest
# --------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()


# Unit test executable
add_executable(eae_tests
    tests/test_firmware.cpp
    src/pid.c
    src/state_machine.c
    src/fault_manager.c
)

target_include_directories(eae_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(eae_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(eae_tests)