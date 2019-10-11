cmake_minimum_required(VERSION 3.15)
project(park_sem1_c_dz1 C)

set(CMAKE_C_STANDARD 11)

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

add_executable(park_sem1_c_dz1 main.c Stack.c MergeSort.c random_utils.c convex_hull.c max_area.c)
add_executable(testStack testStack.c Stack.c Stack.h)
add_executable(testMerge testMerge.c MergeSort.c MergeSort.h random_utils.c)
add_subdirectory(Google_tests)