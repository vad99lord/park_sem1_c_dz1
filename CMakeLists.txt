cmake_minimum_required(VERSION 3.15)
project(park_sem1_c_dz2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#add_executable(park_sem1_c_dz2 BinarySearchST.c FileUtils.c)
add_executable(SeqGen SeqGenFiles.c SequenceGen.c RandomUtils.c FileUtils.c)
add_executable(SeqCounterSingle SequenceCounterMain.c  SequenceCounterSingle.c
        SequenceCounter.c BinarySearchST.c FileUtils.c)
add_executable(SeqCounterMulti SequenceCounterMain.c SequenceCounterMulti.c
        SequenceCounter.c BinarySearchST.c FileUtils.c )
target_link_libraries(SeqCounterMulti pthread )




add_subdirectory(Google_tests/lib/googletest)
include_directories(Google_tests/lib/googletest/googletest/include Google_tests/lib/googletest/googletest/src)



set(SOURCE_FILES )


# CMake instructions to make the static lib

ADD_LIBRARY(SeqCounterLib STATIC SequenceCounter.c BinarySearchST.c FileUtils.c)

ADD_LIBRARY( SeqCounterSingleLib STATIC
        SequenceCounterSingle.c
        )
ADD_LIBRARY(SeqCounterMultiLib SHARED SequenceCounterMulti.c)


set(TARGET_LIBS SeqCounterLib gtest gtest_main)


add_executable(TestST TestST.cpp BinarySearchST.c FileUtils.c)
target_link_libraries(TestST gtest gtest_main)

ADD_EXECUTABLE( TestSingleRand  TestSeqRand.cpp )
ADD_EXECUTABLE( TestMultiRand TestSeqRand.cpp)
ADD_EXECUTABLE( TestSingle  TestSimpleSeq.cpp )
ADD_EXECUTABLE( TestMulti TestSimpleSeq.cpp)

TARGET_LINK_LIBRARIES( TestSingle  ${TARGET_LIBS} SeqCounterSingleLib pthread)
TARGET_LINK_LIBRARIES( TestMulti  ${TARGET_LIBS} SeqCounterMultiLib pthread)
TARGET_LINK_LIBRARIES( TestSingleRand ${TARGET_LIBS} SeqCounterSingleLib pthread)
TARGET_LINK_LIBRARIES( TestMultiRand ${TARGET_LIBS} SeqCounterMultiLib pthread)