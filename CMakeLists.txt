cmake_minimum_required(VERSION 3.16)

project(EAE_Firmware C CXX)

# Use C11 for the firmware
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Build the main firmware simulation
add_executable(eae_firmware
    main.c
    can_sim.c
    cooling_control.c
    fault_manager.c
    pid.c
    state_machine.c
)


# --------------------------------------------------
# GoogleTest
# --------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()


# Build the unit test executable
add_executable(eae_tests
    tests/test_firmware.cpp
    pid.c
    state_machine.c
    fault_manager.c
)

# Allow the tests to find our header files
target_include_directories(eae_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link GoogleTest
target_link_libraries(eae_tests PRIVATE
    GTest::gtest_main
)


include(GoogleTest)

gtest_discover_tests(eae_tests)