#include "SequenceGen.h"
#include "RandomUtils.h"
#include "FileUtils.h"
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define R 127 // num of ASCII chars non extended
#define SPACE 32 //space code ASCII


void generateSeqArray(char *arr, size_t size, int maxLength) {

    //check maxLength boundaries;
    assert (maxLength > 0 && maxLength <= RAND_MAX);
    size_t fullLength = 0;
    //fiil in chars from 0..n-2, n-1=/0;

    char prevC = -1;
    char c = prevC;
    while (fullLength < size) {
        //gen char from 32..126;  32 is space,
        // 126 - last visible char of non extended ASCII

        //loop to get unique new char each time
        while (c == prevC){
            c = random_at_most(R - SPACE - 1) + SPACE;
        }
        prevC = c;
        //length of seq from 1..maxLength from
        size_t length = random_at_most(maxLength - 1) + 1;
        if (length + fullLength > size) {
            //-1 to put /0 in the end
            length = size - fullLength;
        }
        //printf("%c\n", c);
        for (size_t i = fullLength; i < fullLength + length; i++) {
            arr[i] = c;
        }
        //printf("%d %d %d\n", fullLength,c,length);
        fullLength += length;

    }
}
