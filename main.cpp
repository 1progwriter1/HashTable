#include <stdio.h>
#include <assert.h>
#include "src/string_list.h"
#include "../MyLibraries/headers/systemdata.h"
#include "src/measure.h"
#include "src/hash_table.h"

int main(const int argc, const char *argv[]) {

    assert(argv);

    if (argc < 3)   return ERROR;

    int mode = (int) *argv[1] - '0';
    if (mode > MyDjb2 || mode < ZeroHash)   return ERROR;
    const char *file = argv[2];


    size_t (*hash_functions[NUMBER_OF_HASH_FUNC])(char *, size_t) =
    {
    hashFuncZero, hashFuncLetterASCII, hashFuncLength, hashFuncSumASCII, hashFuncCycleShiftLeft, hashFuncCycleShiftRight, hashFuncDjb2
    };

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hash_functions[mode]) != SUCCESS)
        return ERROR;

    if (measureHashTable(&table, file) != SUCCESS)
        return ERROR;

    return SUCCESS;
}