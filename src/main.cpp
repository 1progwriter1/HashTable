#include <stdio.h>
#include <assert.h>
#include "hash_table/string_list.h"
#include "../../MyLibraries/headers/systemdata.h"
#include "measure/measure.h"
#include "hash_table/hash_table.h"

int main(const int argc, const char *argv[]) {

    assert(argv);

    if (argc < 3)   return ERROR;

    int mode = (int) *argv[1] - '0' - 1;
    if (mode > MyDjb2 + 1 || mode < ZeroHash + 1)   return ERROR;
    const char *file = argv[2];


    size_t (*hash_functions[NUMBER_OF_HASH_FUNC])(char *, size_t) =
    {
    hashFuncZero, hashFuncLetterASCII, hashFuncLength, hashFuncSumASCII, hashFuncRol, hashFuncRor, hashFuncDjb2
    };

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hash_functions[mode]) != SUCCESS)
        return ERROR;

    if (measureHashTable(&table, file) != SUCCESS)
        return ERROR;

    return SUCCESS;
}