cmake_minimum_required(VERSION 2.8.8)
project(park_sem1_c_dz1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS "-fpermissive")

set (CPPCHECK_EXCLUDE_DIRS Google_tests/lib/)

set(CMAKE_C_CPPCHECK "cppcheck")
if (CMAKE_C_CPPCHECK)
    list(
            APPEND CMAKE_C_CPPCHECK
            "--enable=warning,style"
            "--suppress=*:${CMAKE_SOURCE_DIR}/${CPPCHECK_EXCLUDE_DIRS}*"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/${CPPCHECK_SUPPRESIONS}"
    )
endif()


# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

add_executable(park_sem1_c_dz1 main.c Stack.c MergeSort.c random_utils.c convex_hull.c max_area.c)
add_executable(testStack testStack.c Stack.c Stack.h)
add_executable(testMerge testMerge.c MergeSort.c MergeSort.h random_utils.c)
#add_subdirectory(Google_tests)
enable_testing()
set(SOURCE_FILES Google_tests/testMerge.cpp Google_tests/testStack.cpp Google_tests/testHull.cpp Google_tests/testArea.cpp MergeSort.c random_utils.c convex_hull.c Stack.c max_area.c)
add_executable(Google_tests_run ${SOURCE_FILES})
target_link_libraries(Google_tests_run ${GTEST_BOTH_LIBRARIES} gtest gtest_main )