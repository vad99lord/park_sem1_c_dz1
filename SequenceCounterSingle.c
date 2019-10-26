#include "SequenceCounter.h"
#include <stdio.h>

//returns most common length and char of sequence
Sequence findCommonLength(const BinarySearchST* st){

    int *keys = malloc(sizeof(int) * sizeST(st));
    iteratorKeys(st, keys);
    SeqCount *values = malloc(sizeof(SeqCount) * sizeST(st));
    iteratorValues(st, values);
    int maxCountInd = 0;
    for (size_t i = 1; i < sizeST(st); i++) {
        if (values[i].count > values[maxCountInd].count) {
            maxCountInd = i;
        }
    }
    Sequence result = {keys[maxCountInd],values[maxCountInd].elem};
    free(values);
    free(keys);
    return result;
}


//counts all sequences in buffer to BinaryST
void countSequences(const char *buf, size_t size, BinarySearchST* st) {

    printf("%s\n","Single-Thread implementation");

    char curSymbol = buf[0];
    char prevSymbol = curSymbol;
    long length = 1;

    void *sc = malloc(sizeof(SeqCount));
    for (size_t i = 1; i <= size; i++) {
        curSymbol = buf[i];
        if (curSymbol != prevSymbol) {
            //if new length => add to ST
            if (get(&length, sc, st) == NO_KEY) {
                //init new struct and put to array
                ((SeqCount *) sc)->count = 1;
                ((SeqCount *) sc)->elem = prevSymbol;
            }
                //else update counter for specified length
            else {
                ((SeqCount *) sc)->count++;

            }
            put(&length, sc, st);
            length = 1;
        } else {
            length++;
        }
        prevSymbol = curSymbol;
    }
    /*
    for (int i = 0; i < keys[maxCountInd]; i++) {
        printf("%c",
               values[maxCountInd].elem);
    }
    */
    free(sc);
}

