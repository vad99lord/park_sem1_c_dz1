//
// Created by vadim on 24.10.2019.
//

#ifndef PARK_SEM1_C_DZ2_FILEUTILS_H
#define PARK_SEM1_C_DZ2_FILEUTILS_H

#include <stdlib.h>

/** Read full contents of file to buffer
@param fileName - filename of file to be read
@param size - reference of number to store length of buffer
@return char* pointer to block of read chars
*/
char* readFile(const char *fileName, size_t* size);

/** Write full contents of buffer to file
@param fileName - filename of file to write, new file will be created if not found
@param buf -  pointer to block of chars to be written
@param size - reference of number to store length of buffer
**/
void writeToFile(const char* fileName, const char* buf, size_t size);

//Deletes buffer memory
void deleteBuf(char* );


#endif //PARK_SEM1_C_DZ2_FILEUTILS_H
