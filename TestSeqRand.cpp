#include <gtest/gtest.h>

extern "C" {
#include "BinarySearchST.h"
#include "FileUtils.h"
#include "SequenceCounter.h"
}

static const int FilesCount = 3;
static const int SmallLength = 10;

TEST(SeqCountRand, ValidityTest) {

    std::string fileNames[] = { "RandSmall.txt","RandMedium.txt","RandLarge.txt"};
    int maxLength[] = {SmallLength,SmallLength*10,SmallLength*100};

    for (int i =0 ;i<FilesCount;i++){
        size_t size = 0;
        char *buffer = readFile(fileNames[i].c_str(), &size);
        clock_t begin = clock();
        Sequence seq = findCommonSeq(buffer, size);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Time elapsed: %f\n", time_spent);


        printf("Most common length: %ld, character: %c\n", seq.length,seq.elem);
        for (long i = 0; i < seq.length; i++) {
            printf("%c",seq.elem);
        }
        printf("\n");
        ASSERT_TRUE(seq.length<=maxLength[i]);

        deleteBuf(buffer);
    }
}






