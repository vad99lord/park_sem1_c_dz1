#include <time.h>
#include "SequenceGen.h"
#include "FileUtils.h"

#define FilesCount 3
#define SmallSize 10000
#define SmallLength 10

int main() {
    srand(time(NULL));
    char** filenames = malloc(FilesCount*sizeof(char*));
    filenames[0] = "../RandSmall.txt";
    filenames[1] = "../RandMedium.txt";
    filenames[2] = "../RandLarge.txt";
    size_t size[] = {SmallSize,SmallSize*100,SmallSize*10000};
    int maxLength[] = {SmallLength,SmallLength*10,SmallLength*100};
    for (int i = 0; i<FilesCount;i++) {
        char *arr = malloc(size[i]);
        generateSeqArray(arr, size[i], maxLength[i]);
        //arr[size-1] = 0;
        //printf("%s\n", arr);
        writeToFile(filenames[i], arr, size[i]);
        free(arr);
    }
    free(filenames);
}

