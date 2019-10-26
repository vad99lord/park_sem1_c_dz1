

#ifndef PARK_SEM1_C_DZ2_SEQUENCECOUNTER_H
#define PARK_SEM1_C_DZ2_SEQUENCECOUNTER_H


#include <stdlib.h>
#include "BinarySearchST.h"

struct SeqCount{
    int count;
    char elem;
};

typedef struct SeqCount SeqCount;

struct Sequence{
    long length;
    char elem;
};

typedef struct Sequence Sequence;



//sample compare function for ints
static int compareInts(const void *p, const void *q);

//finds most common length of sequence in buffer and returns it representative;
Sequence findCommonSeq(const char *buf, size_t size);

//counts all sequences in buffer to BinaryST
void countSequences(const char *buf, size_t size, BinarySearchST* st);

//returns most common length and char of sequence
Sequence findCommonLength(const BinarySearchST* st);


#endif //PARK_SEM1_C_DZ2_SEQUENCECOUNTER_H
