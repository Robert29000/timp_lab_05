cmake_minimum_required(VERSION 3.4)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https:\//github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
    SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab05)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

include_directories(banking)
add_subdirectory(banking banking)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
 enable_testing()
 add_executable(check tests/bank_test.cpp)
 target_compile_options(check PRIVATE --coverage)
 target_link_libraries(check banking GTest::gtest_main Gtest::gmock_main --coverage)
 add_test(NAME check COMMAND check)
endif()
