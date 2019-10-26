#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "BinarySearchST.h"
#include <sys/sysinfo.h>
#include "SequenceCounter.h"

// Lock shared resources among threads
pthread_mutex_t lock;

#define MAX_THREAD get_nprocs() //number of available processors

struct ThreadArgs {
    const char* buf;
    size_t startPos; //start pos of search for thread
    size_t endPos; //end pos of search for thread
    BinarySearchST *st; //ST for use across threads;
    int thread; //num of thread
    Sequence startSeq; //structure to hold start seq of thread
    Sequence endSeq; //structure to hold end seq of thread

};
typedef struct ThreadArgs CounterArgs;

struct ThreadMaxArgs {
    const BinarySearchST *st; //ST for use across threads;
    size_t startPos; //start pos of search for thread
    size_t endPos; //end pos of search for thread
    int mLength; //biggest counter value in segment
    bool startThread;
};
typedef struct ThreadMaxArgs MaxArgs;



static void* countSeqThread(void* args) {
    CounterArgs counterArgs = *((CounterArgs*)args);
    char curSymbol = counterArgs.buf[counterArgs.startPos];
    char prevSymbol = curSymbol;
    long length = 1;

    int seqCounter = 1;
    BinarySearchST *st = counterArgs.st;
    void *sc = malloc(sizeof(SeqCount));
    for (size_t i = counterArgs.startPos+1;
         i <= counterArgs.endPos+1; i++) {
        //printf("%zu -> %d\n",i,counterArgs.thread);
        //if pos is right+1 => simulate /0 ending for segment
        if (i == counterArgs.endPos+1) {
            curSymbol = 0;
            //if not first seq in segment && segment ends => assign to end seq
            if (seqCounter != 1){
                ((CounterArgs*)args)->endSeq.length = length;
                ((CounterArgs*)args)->endSeq.elem = prevSymbol;
            }
        }
        else{
            curSymbol = counterArgs.buf[i];
        }
        if (curSymbol != prevSymbol) {

            //if start seq ends => assign to thread args seq
            if (seqCounter == 1){
                ((CounterArgs*)args)->startSeq.length = length;
                ((CounterArgs*)args)->startSeq.elem = prevSymbol;
            }
            seqCounter++;

            //atomic operations block starts
            if (pthread_mutex_lock(&lock) != 0){
                fprintf(stderr, "%s\n","error: Cannot lock mutex");
                break;
            }
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

            if (pthread_mutex_unlock(&lock) != 0){
                fprintf(stderr, "%s\n","error: Cannot lock mutex");
                break;
            }
            //atomic operations block ends

            length = 1;
        } else {
            length++;
        }
        prevSymbol = curSymbol;
    }

    free(sc);
    pthread_exit(0);
}


static void* findMaxThread(void* args) {
    MaxArgs maxArgs = *((MaxArgs*)args);
    SeqCount *values = malloc(sizeof(SeqCount) * (maxArgs.endPos - maxArgs.startPos + 1));
    //get values from lo..hi from st
    iteratorValuesRange(maxArgs.st, values, maxArgs.startPos, maxArgs.endPos);
    int maxCountInd = 0;
    for (size_t i = 1; i <= maxArgs.endPos-maxArgs.startPos; i++) {
        if (values[i].count > values[maxCountInd].count) {
            maxCountInd = i;
        }
    }
    ((MaxArgs*)args)->mLength = (int)maxArgs.startPos+maxCountInd;
    free(values);
    pthread_exit(0);
}


//Adjust found sequences by checking start/end seqs of each segment
static void adjustBorders(const CounterArgs* counterArgs, BinarySearchST* st){
    void *sc = malloc(sizeof(SeqCount));

    bool notSeqEnd = false;
    long mergeSeqLength = 0;
    for (int i = 0; i < MAX_THREAD; ++i)
    {
        if (notSeqEnd){
            //if prev segment was 1 seq only
            if (counterArgs[i-1].endSeq.length == 0) {
                //if seq continues in new segment
                if (counterArgs[i].startSeq.elem == counterArgs[i - 1].startSeq.elem) {
                    //decrement counterArgs[i-1].start.length in st
                    //mergeSeqLength += [i-1]length
                    get(&counterArgs[i - 1].startSeq.length, sc, st);
                    ((SeqCount *) sc)->count--;
                    put(&counterArgs[i - 1].startSeq.length, sc, st);
                    mergeSeqLength += counterArgs[i-1].startSeq.length;
                }
                else{
                    notSeqEnd = false;
                }
            }
            else {
                //if seq continues in new segment
                if (counterArgs[i].startSeq.elem == counterArgs[i-1].endSeq.elem){
                    //decrement counterArgs[i-1].endSeq.length in st
                    //mergeSeqLength += [i-1]length
                    get(&counterArgs[i - 1].endSeq.length, sc, st);
                    ((SeqCount *) sc)->count--;
                    put(&counterArgs[i - 1].endSeq.length, sc, st);
                    mergeSeqLength += counterArgs[i-1].endSeq.length;
                }
                else {
                    notSeqEnd = false;
                }
            }
        }

        //if only 1 seq was found in segment && checking not last segment currently
        if (counterArgs[i].endSeq.length == 0 && i != MAX_THREAD-1){
            notSeqEnd = true;
        }
        else{
            if (notSeqEnd) {
                //decrement counterArgs[i].start.length in st
                //mergeSeqLength += [i]length
                //add to st mergeLength;
                //mergeLength = 0;
                get(&counterArgs[i].startSeq.length, sc, st);
                ((SeqCount *) sc)->count--;
                put(&counterArgs[i].startSeq.length, sc, st);

                mergeSeqLength += counterArgs[i].startSeq.length;

                //printf("Merge - %ld : %c\n", mergeSeqLength,counterArgs[i].startSeq.elem);
                if (get(&mergeSeqLength, sc, st) == NO_KEY) {
                    //init new struct and put to array
                    ((SeqCount *) sc)->count = 1;
                }
                else {
                    ((SeqCount *) sc)->count++;
                }
                //update char in case it is not correct
                ((SeqCount *) sc)->elem = counterArgs[i].startSeq.elem;
                put(&mergeSeqLength, sc, st);

                mergeSeqLength = 0;
            }
            notSeqEnd = true;
        }

    }
    free(sc);

}


//returns most common length and char of sequence
Sequence findCommonLength(const BinarySearchST* st){

    MaxArgs maxArgs[MAX_THREAD];
    pthread_t threads[MAX_THREAD];

    int *keys = malloc(sizeof(int) * sizeST(st));
    iteratorKeys(st, keys);

    for (int i = 0; i < MAX_THREAD; i++) {
        maxArgs[i].st = st;
        maxArgs[i].startPos = i * sizeST(st) / MAX_THREAD;
        if (i > 0) {
            maxArgs[i].startPos++;
        }
        maxArgs[i].endPos = (i + 1) * sizeST(st) / MAX_THREAD;
        if  (maxArgs[i].endPos>=sizeST(st)) {
            maxArgs[i].endPos = sizeST(st)-1;
        }
        //segment too small => no need to start thread
        if (maxArgs[i].startPos >= maxArgs[i].endPos){
            if  (maxArgs[i].startPos >= sizeST(st)) {
                maxArgs[i].startPos = sizeST(st)-1;
            }
            maxArgs[i].mLength = maxArgs[i].startPos;
            maxArgs[i].startThread = false;
        }
        else {
            maxArgs[i].mLength = 0;
            maxArgs[i].startThread = true;
        }
    }


    for (int i = 0; i < MAX_THREAD; i++)
    {
        if (maxArgs[i].startThread) {
            if (pthread_create(&threads[i], NULL, findMaxThread, &maxArgs[i]) != 0) {
                fprintf(stderr, "error: Cannot create thread # %d\n", i);
                break;
            }
        }

    }

    for (int i = 0; i < MAX_THREAD; ++i)
    {
        if (maxArgs[i].startThread) {
            if (pthread_join(threads[i], NULL) != 0) {
                fprintf(stderr, "error: Cannot join thread # %d\n", i);
            }
        }
    }

    SeqCount *values = malloc(sizeof(SeqCount) * sizeST(st));
    iteratorValues(st, values);
    /*for (int i = 0; i < MAX_THREAD; ++i)
    {
        printf("%d max  key= %d,count = %d\n", i, keys[maxArgs[i].mLength],
               values[maxArgs[i].mLength].count);
    }*/
    int maxCountInd = 0;
    for (size_t i = 1; i < MAX_THREAD; i++) {
        if (values[maxArgs[i].mLength].count > values[maxArgs[maxCountInd].mLength].count) {
            maxCountInd = i;
        }
    }
    /*printf("%s","Threads max = ");
    for (int i = 0; i < keys[maxArgs[maxCountInd].mLength]; i++) {
        printf("%c",
               values[maxArgs[maxCountInd].mLength].elem);
    }
    printf("\n");
    */
    Sequence result = {keys[maxArgs[maxCountInd].mLength],values[maxArgs[maxCountInd].mLength].elem};

    free(values);
    free(keys);

    return result;
}


void countSequences(const char *buf, size_t size, BinarySearchST* st) {

    printf("%s\n","Multi-Thread implementation");

    CounterArgs counterArgs[MAX_THREAD];

    pthread_t threads[MAX_THREAD];

    for (int i = 0; i < MAX_THREAD; i++) {
        counterArgs[i].buf = buf;
        counterArgs[i].startPos = i * size / MAX_THREAD;
        if (i > 0) {
            counterArgs[i].startPos++;
        }
        counterArgs[i].endPos = (i + 1) * size / MAX_THREAD;
        counterArgs[i].st = st;
        counterArgs[i].thread = i;
        Sequence defArgs = { .elem = 0, .length = 0 };
        counterArgs[i].startSeq = defArgs;
        counterArgs[i].endSeq = defArgs;
    }
    for (int i = 0; i < MAX_THREAD; i++)
    {
        if (pthread_create(&threads[i], NULL, countSeqThread, &counterArgs[i]) != 0)
        {
            fprintf(stderr, "error: Cannot create thread # %d\n", i);
            break;
        }

    }

    for (int i = 0; i < MAX_THREAD; ++i)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            fprintf(stderr, "error: Cannot join thread # %d\n", i);
        }
    }

    void *sc = malloc(sizeof(SeqCount));

    /*
    //print start end seqs
    for (int i = 0; i < MAX_THREAD; ++i)
    {
        printf("Start - %ld : %c\n", counterArgs[i].startSeq.length,counterArgs[i].startSeq.elem);
        printf("End - %ld : %c\n", counterArgs[i].endSeq.length,counterArgs[i].endSeq.elem);
    }
    */

    //adjust borders of segments
    adjustBorders(counterArgs,st);

    free(sc);
}
