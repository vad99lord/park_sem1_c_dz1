#include <stdio.h>
#include <string.h>
#include <time.h>
#include "FileUtils.h"
#include "SequenceCounter.h"
int main() {
    size_t size = 0;
    char *buffer = readFile("../smallDuplicate.txt", &size);

    //printf("%s\n", buffer);

    clock_t begin = clock();
    Sequence seq = findCommonSeq(buffer, size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f\n", time_spent);


    printf("Most common length: %ld, character: %c\n", seq.length,seq.elem);
    for (long i = 0; i < seq.length; i++) {
        printf("%c",seq.elem);
    }

    deleteBuf(buffer);
    return 0;
}

