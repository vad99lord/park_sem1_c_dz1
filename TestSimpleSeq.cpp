#include <gtest/gtest.h>

extern "C" {
#include "BinarySearchST.h"
#include "FileUtils.h"
#include "SequenceCounter.h"
}


TEST(SeqCount, ValidityTest) {

    size_t size = 0;
    char *buffer = readFile("../smallDuplicate.txt", &size);
    Sequence seq = findCommonSeq(buffer, size);
    std::cout << "Testing file with one long sequence.....\n";
    ASSERT_TRUE(seq.elem=='j');
    ASSERT_TRUE(seq.length==11);
    deleteBuf(buffer);

    size = 0;
    buffer = readFile("../samplesmall.txt", &size);
    seq = findCommonSeq(buffer, size);
    std::cout << "Testing small string with no duplicates....\n";
    ASSERT_TRUE(seq.length==2||seq.length==3);
    deleteBuf(buffer);

    size = 0;
    buffer = readFile("../sample.txt", &size);
    seq = findCommonSeq(buffer, size);
    std::cout << "Testing medium sample with many small sequences....\n";
    printf("\n");
    ASSERT_TRUE(seq.length==1);
    deleteBuf(buffer);


}




