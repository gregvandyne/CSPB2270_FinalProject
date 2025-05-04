cmake_minimum_required(VERSION 3.10)
project(FenwickVotingSystem)

set(CMAKE_CXX_STANDARD 17)

# Google Test
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# Main App
add_executable(voting_app
    main.cpp
    FenwickTree.cpp
    PollManager.cpp
    PollCollection.cpp
    Survey.cpp
    UIHelper.cpp
)

# Test App
add_executable(run_tests
    tests/test_fenwick.cpp
    tests/test_poll_collection.cpp
    FenwickTree.cpp
    PollManager.cpp
    PollCollection.cpp
    Survey.cpp
    UIHelper.cpp
)

target_link_libraries(run_tests gtest gtest_main)
