#include "SequenceCounter.h"
#include <stdlib.h>
#include <string.h>
#include "BinarySearchST.h"


//sample compare function for ints
static int compareInts(const void *p, const void *q) {
    return *(const int *) p - *(const int *) q;
}


//finds most common length of sequence in buffer and returns it representative;
Sequence findCommonSeq(const char *buf, size_t size){
    BinarySearchST *st = createEmptyST(sizeof(int), sizeof(SeqCount), compareInts);
    countSequences(buf,size,st);
    //find most common length by finding max counter
    Sequence sequence = findCommonLength(st);
    deleteST(st);
    return sequence;
}