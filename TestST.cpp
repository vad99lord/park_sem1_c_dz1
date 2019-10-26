#include <gtest/gtest.h>

extern "C" {
#include "BinarySearchST.h"
#include "FileUtils.h"
}

//sample compare function for ints
int compare_chars(const void *p, const void *q) {
    return *(const char *) p - *(const char *) q;
}

TEST(BinSearchTests, ValidityTest) {

    size_t sizeB = 0;
    char* buffer = readFile("../tinyST.txt",&sizeB);

    //printf("%s\n", buffer);

    BinarySearchST *st = createEmptyST(sizeof(char), sizeof(int), compare_chars);

    for (size_t i = 0; i < sizeB; i++) {
        put(&buffer[i], &i, st);
    }

    char *keys = (char*) malloc(sizeof(char) * sizeST(st));
    iteratorKeys(st, keys);
    void *val = malloc(sizeof(int));
    char s = 'S';
    int value = 100;
    ASSERT_TRUE(get(&s,val,st) != NO_KEY);
    put(&s,&value,st);
    s = 'X';
    value = 200;
    put(&s,&value,st);
    s = 'p';
    printf("\n");
    ASSERT_TRUE(get(&s,val,st) == NO_KEY);
    for (size_t i = 0; i < sizeST(st); i++) {
        get(&keys[i], val, st);
        printf("%c,%d\n", keys[i], *((int *) val));
        //StdOut.println(s + " " + st.get(s));
    }
    int v;
    get(&keys[0], val, st);
    v = *((int *) val);
    EXPECT_EQ(keys[0],'A');
    EXPECT_EQ(v,8);

    get(&keys[5], val, st);
    v = *((int *) val);
    EXPECT_EQ(keys[5],'M');
    EXPECT_EQ(v,9);

    get(&keys[sizeST(st)-1], val, st);
    v = *((int *) val);
    EXPECT_EQ(keys[sizeST(st)-1],'X');
    EXPECT_EQ(v,200);

    s = 'S';
    get(&s, val, st);
    v = *((int *) val);
    EXPECT_EQ(v,100);

    s = 'o';
    ASSERT_TRUE(get(&s,val,st) == NO_KEY);
    free(val);
    deleteBuf(buffer);
    free(keys);
    deleteST(st);
}


