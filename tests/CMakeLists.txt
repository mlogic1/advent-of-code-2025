add_executable(advent_tests advent_test.cpp)
target_link_libraries(advent_tests PRIVATE advent2025)

add_test(NAME TestDay01 COMMAND advent_tests 01 ../../inputs/file)