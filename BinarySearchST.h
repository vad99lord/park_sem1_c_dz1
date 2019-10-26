//
// Created by vadim on 24.10.2019.
//

#ifndef PARK_SEM1_C_DZ2_BINARYSEARCHST_H
#define PARK_SEM1_C_DZ2_BINARYSEARCHST_H


#define INIT_CAPACITY 2
#define NO_KEY -1
#define NO_ITEMS -2

#include <stdlib.h>
#include <stdbool.h>

//Ordered symbol table based on ordered resizing array

// A structure to represent a binary search ST
struct BinarySearchST;

typedef struct BinarySearchST BinarySearchST;

//Initializes an empty symbol table with the specified initial capacity.
BinarySearchST *createST(size_t capacity, size_t kSize, size_t vSize,
                         int (*comp)(const void *, const void *));

// create an empty symbol table with the specified initial capacity
BinarySearchST *createEmptyST(size_t kSize, size_t vSize,
                              int (*comp)(const void *, const void *));
// resize the underlying arrays
static void resize(size_t capacity, BinarySearchST *st);

//Returns the number of key-value pairs in this symbol table.
size_t sizeST(const BinarySearchST *st);

//Returns true if this symbol table is empty.
bool isEmpty(const BinarySearchST *st);

//Returns the number of keys in this symbol table strictly less than key.
//which is key pos in array
static int rank(const void *key, const BinarySearchST *st);

//Returns the value associated with the given key in this symbol table.
//returns NO_KEY if key is not found
//else positive integer
int get(const void *key, void *src, const BinarySearchST *st);

//Inserts the specified key-value pair into the symbol table, overwriting the old
//value with the new value if the symbol table already contains the specified key.
void put(const void *key, const void *val, BinarySearchST *st);

//Returns all keys in this symbol table as an array.
//return no items if ST is empty
//else positive integer
int iteratorKeys(const BinarySearchST *st, void *buffer);

//Returns all values in this symbol table as an array.
//return no items if ST is empty
//else positive integer
int iteratorValues(const BinarySearchST *st, void *buffer);

//Returns values from lo to hi inclusively in this symbol table as an array.
//return no items if ST is empty
//else positive integer
int iteratorValuesRange(const BinarySearchST *st, void *buffer, size_t lo, size_t hi);

//free memory connected with ST
void deleteST(BinarySearchST *st);

#endif //PARK_SEM1_C_DZ2_BINARYSEARCHST_H
