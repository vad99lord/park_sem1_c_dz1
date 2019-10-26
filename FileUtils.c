#include "FileUtils.h"
#include <stdio.h>

char* readFile(const char* fileName, size_t* size){

    FILE *f = fopen(fileName, "r");
    if(f == NULL)
    {
        printf("ERROR - Failed to open file for reading\n");
        exit(1);
    }

    //seek eof position
    fseek(f, 0, SEEK_END);
    //get position => num of chars
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    //alloc new buffer to store file contents + /0
    char* buf = malloc(fsize+1);

    fread(buf, sizeof(char), fsize, f);
    fclose(f);

    //set last char to /0
    buf[fsize] = 0;

    //set size to num of chars
    *size = fsize;

    return buf;
}


//write contents of buffer to file
void writeToFile(const char* fileName, const char* buf, size_t size){
    // open file for writing or create if doesn't exist
    FILE *f = fopen(fileName,"w+");

    // write buffer, exit, if operation is failed
    if(fwrite(buf, sizeof(char), size, f) != size)
    {
        printf("ERROR - Failed to write %zu bytes to file\n", size);
        exit(1);
    }

    //close file
    fclose(f);
}



void deleteBuf(char* buf){
    free(buf);
}