# 'Google_test' is the subproject name
project(Google_tests_run)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES testMerge.cpp testStack.cpp testHull.cpp testArea.cpp ../MergeSort.c ../random_utils.c ../convex_hull.c ../Stack.c ../max_area.c)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include lib/googletest/googletest/src)
include_directories(park_sem1_algos)
# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_tests_run ${SOURCE_FILES})
target_link_libraries(Google_tests_run gtest gtest_main)