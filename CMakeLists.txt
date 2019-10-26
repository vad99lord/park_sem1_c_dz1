cmake_minimum_required(VERSION 2.8.8)
project(park_sem1_c_dz2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

ADD_LIBRARY(SeqCounterLib STATIC SequenceCounter.c BinarySearchST.c FileUtils.c)

ADD_LIBRARY( SeqCounterSingleLib STATIC
        SequenceCounterSingle.c
        )
ADD_LIBRARY(SeqCounterMultiLib SHARED SequenceCounterMulti.c)


#add_executable(park_sem1_c_dz2 BinarySearchST.c FileUtils.c)
add_executable(SeqGen SeqGenFiles.c SequenceGen.c RandomUtils.c FileUtils.c)
add_executable(SeqCounterSingle SequenceCounterMain.c )
add_executable(SeqCounterMulti  SequenceCounterMain.c )

TARGET_LINK_LIBRARIES(SeqCounterSingle SeqCounterSingleLib SeqCounterLib)
TARGET_LINK_LIBRARIES(SeqCounterMulti SeqCounterMultiLib SeqCounterLib pthread )



#add_subdirectory(Google_tests/lib/googletest)
#include_directories(Google_tests/lib/googletest/googletest/include Google_tests/lib/googletest/googletest/src)

# CMake instructions to make the static lib




set(TARGET_LIBS SeqCounterLib gtest gtest_main)


add_executable(TestST TestST.cpp BinarySearchST.c FileUtils.c)
target_link_libraries(TestST gtest gtest_main ${GTEST_BOTH_LIBRARIES}  pthread)

ADD_EXECUTABLE( TestSingleRand  TestSeqRand.cpp )
ADD_EXECUTABLE( TestMultiRand TestSeqRand.cpp)
ADD_EXECUTABLE( TestSingle  TestSimpleSeq.cpp )
ADD_EXECUTABLE( TestMulti TestSimpleSeq.cpp)

TARGET_LINK_LIBRARIES( TestSingle  ${TARGET_LIBS} SeqCounterSingleLib ${GTEST_BOTH_LIBRARIES}  pthread)
TARGET_LINK_LIBRARIES( TestMulti  ${TARGET_LIBS} SeqCounterMultiLib ${GTEST_BOTH_LIBRARIES}  pthread)
TARGET_LINK_LIBRARIES( TestSingleRand ${TARGET_LIBS} SeqCounterSingleLib ${GTEST_BOTH_LIBRARIES}  pthread)
TARGET_LINK_LIBRARIES( TestMultiRand ${TARGET_LIBS} SeqCounterMultiLib ${GTEST_BOTH_LIBRARIES}  pthread)