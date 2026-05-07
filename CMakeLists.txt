cmake_minimum_required(VERSION 3.14)

project(RegistrationServiceTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

add_executable(registration_tests
    registration_service_test.cpp
    registration_service.cpp
)

target_link_libraries(registration_tests
    PRIVATE
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(registration_tests)