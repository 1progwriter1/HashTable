#include <stdio.h>
#include <assert.h>
#include "../measure/measure.h"
#include "../../../MyLibraries/headers/systemdata.h"
#include "../hash_table/hash_table.h"
#include "../../../MyLibraries/headers/file_func.h"
#include <stdlib.h>

int measureHashTable(HashTableStr *table, const char *filename);

int main(const int argc, const char *argv[]) {

    assert(argv);

    if (argc < 3)   return ERROR;

    int mode = (int) *argv[1] - '0' - 1;
    if (mode > CRC32 || mode < ZeroHash)    return ERROR;
    const char *file = argv[2];

    size_t (*hash_functions[NUMBER_OF_HASH_FUNC])(char *, size_t) =
    {
    hashFuncZero, hashFuncLetterASCII, hashFuncLength, hashFuncSumASCII, hashFuncRol, hashFuncRor, hashFuncDjb2Asm, hashFuncCRC32
    };

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hash_functions[mode]) != SUCCESS) {
        printf(RED "hash_table error: " END_OF_COLOR "creation failed\n");
        return ERROR;
    }

    if (measureHashTable(&table, file) != SUCCESS) {
        printf(RED "hash_table error: " END_OF_COLOR "measurement failed\n");
        return ERROR;
    }

    return SUCCESS;
}

int measureHashTable(HashTableStr *table, const char *filename) {

    assert(filename);
    assert(table);

    if (loadHashTable(table, SRC_FILE) != SUCCESS) {
        printf(RED "hash_table error: " END_OF_COLOR "load failed\n");
        return ERROR;
    }

    FILE *fn = openFile(filename, WRITE);
    if (!fn) return FILE_OPEN_ERROR;

    fprintf(fn, "index,size\n");
    for (size_t i = 0; i < table->size; i++)
        fprintf(fn, "%lu, %lu\n", i, table->lists[i].size);

    closeFile(fn);

    return SUCCESS;
}