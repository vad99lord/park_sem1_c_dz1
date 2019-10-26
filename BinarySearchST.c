#include <assert.h>
#include <string.h>
#include "BinarySearchST.h"

struct BinarySearchST {
    void *keys; //container for keys
    void *vals; //container for values
    size_t n; //number of elements in ST
    size_t capacity; //capacity of ST
    size_t keySize; //sizeST of 1 key of ST
    size_t valSize; //sizeST of 1 val of ST
    int (*comp)(const void *, const void *); //comparator function for ST
};


//Initializes an empty symbol table with the specified initial capacity.
BinarySearchST *createST(size_t capacity, size_t kSize, size_t vSize,
                         int (*comp)(const void *, const void *)) {
    BinarySearchST *st = malloc(sizeof(BinarySearchST));
    st->capacity = capacity;
    st->n = 0;
    st->keySize = kSize;
    st->valSize = vSize;
    st->keys = malloc(capacity * kSize);
    memset(st->keys,0, capacity);
    st->vals = malloc(capacity * vSize);
    memset(st->vals,0, capacity);
    st->comp = comp;
    return st;
}

// create an empty symbol table with the specified initial capacity
BinarySearchST *createEmptyST(size_t kSize, size_t vSize,
                              int (*comp)(const void *, const void *)) {
    return createST(INIT_CAPACITY, kSize, vSize, comp);
}

// resize the underlying arrays
static void resize(size_t capacity, BinarySearchST *st) {
    assert (capacity >= st->n);
    void *tempK = malloc(capacity * st->keySize);
    memset(tempK,0, capacity);
    void *tempV = malloc(capacity * st->valSize);
    memset(tempV,0, capacity);
    st->capacity = capacity;

    memcpy(tempK, st->keys, st->n * st->keySize);
    memcpy(tempV, st->vals, st->n * st->valSize);
    //free previous array memory
    free(st->vals);
    free(st->keys);
    st->vals = tempV;
    st->keys = tempK;
}


//Returns the number of key-value pairs in this symbol table.
size_t sizeST(const BinarySearchST *st) {
    return st->n;
}

//Returns true if this symbol table is empty.
bool isEmpty(const BinarySearchST *st) {
    return st->n == 0;
}

// are the items in the array in ascending order?
static bool isSorted(BinarySearchST *st) {
    for (size_t i = 1; i < st->n; i++)
        if (st->comp(&((const char *) st->keys)[i * st->keySize], &((const char *) st->keys)[(i - 1) * st->keySize]) <
            0)
            return false;
    return true;
}

//Returns the number of keys in this symbol table strictly less than key.
//which is key pos in array
static int rank(const void *key, const BinarySearchST *st) {
    size_t lo = 0;
    if (st->n == 0){
        return lo;
    }
    size_t hi = st->n - 1;
    while (lo <= hi) {
        size_t mid = lo + (hi - lo) / 2;
        //comp(&((const char *) aux)[j * size], &((const char *) aux)[i * sizeST]) < 0
        //int cmp = key.compareTo(st->keys[mid]);
        int cmp = st->comp(key, &((const char *) st->keys)[mid * st->keySize]);
        if (cmp < 0) {
            //if hi is becoming -1 => break loop and return lo
            if (mid == 0){
                break;
            }
            hi = mid - 1;
        }

        else if (cmp > 0) lo = mid + 1;
        else return mid;
    }
    return lo;
}


//Returns the value associated with the given key in this symbol table.
//returns NO_KEY if key is not found
//else positive integer
int get(const void *key, void *src, const BinarySearchST *st) {
    if (isEmpty(st)) {
        return NO_KEY;
    }
    int i = rank(key, st);
    //keys[i].compareTo(key) == 0
    if (i < st->n && st->comp(&((const char *) st->keys)[i * st->keySize], key) == 0) {
        //copy value to src pointer;
        memcpy(src, &((char *) st->vals)[i * st->valSize], st->valSize);
        return 1;
    }
    return NO_KEY;
}

//Inserts the specified key-value pair into the symbol table, overwriting the old
//value with the new value if the symbol table already contains the specified key.
void put(const void *key, const void *val, BinarySearchST *st) {
    int i = rank(key, st);

    // key is already in table
    if (i < st->n && st->comp(&((const char *) st->keys)[i * st->keySize], key) == 0) {
        memcpy(&((char *) st->vals)[i * st->valSize], val, st->valSize);
        //vals[i] = val;
        return;
    }

    // insert new key-value pair
    if (st->n == st->capacity) resize(2 * st->capacity, st);

    /*for (int j = n; j > i; j--)  {
        keys[j] = keys[j-1];
        vals[j] = vals[j-1];
    }*/
    if (i < st->n) {
        memmove(&((char *) st->vals)[(i + 1) * st->valSize],
                &((char *) st->vals)[i * st->valSize], (st->n - i) * st->valSize);
        memmove(&((char *) st->keys)[(i + 1) * st->keySize],
                &((char *) st->keys)[i * st->keySize], (st->n - i) * st->keySize);
    }

    //keys[i] = key;
    //vals[i] = val;
    memcpy(&((char *) st->vals)[i * st->valSize], val, st->valSize);
    memcpy(&((char *) st->keys)[i * st->keySize], key, st->keySize);
    st->n++;
    assert (isSorted(st));
}


//Returns all keys in this symbol table as an array.
//return no items if ST is empty
//else positive integer
int iteratorKeys(const BinarySearchST *st, void *buffer) {
    if (isEmpty(st)) {
        return NO_ITEMS;
    }
    memcpy(buffer, st->keys, st->n * st->keySize);
    return 1;
}

//Returns all values in this symbol table as an array.
//return no items if ST is empty
//else positive integer
int iteratorValues(const BinarySearchST *st, void *buffer) {
    if (isEmpty(st)) {
        return NO_ITEMS;
    }
    memcpy(buffer, st->vals, st->n * st->valSize);
    return 1;
}

int iteratorValuesRange(const BinarySearchST *st, void *buffer, size_t lo, size_t hi){
    //check bounds of range
    assert(lo>=0 && lo<=hi);
    if (isEmpty(st)) {
        return NO_ITEMS;
    }
    memcpy(buffer, &((char *) st->vals)[lo*st->valSize], (hi-lo+1) * st->valSize);
    return 1;
}

//free memory connected with ST
void deleteST(BinarySearchST *st) {
    free(st->keys);
    free(st->vals);
    free(st);
}






