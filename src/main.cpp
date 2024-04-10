#include <stdio.h>
#include <assert.h>
#include "hash_table/string_list.h"
#include "../../MyLibraries/headers/systemdata.h"
#include "../../MyLibraries/headers/file_func.h"
#include "measure/measure.h"
#include "hash_table/hash_table.h"

const int m = MAX_WORD_LEN;

int main(const int argc, const char *argv[]) {

    assert(argv);

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hashFuncCRC32) != SUCCESS)
        return ERROR;



    hashTableStrDtor(&table);

    return SUCCESS;
}

int loadHashTableStr(HashTableStr *table, const char *filename) {

    assert(table);
    assert(filename);

    char *buf = readFileToBuffer(filename);
    if (!buf)   return ERROR;

    char

    return SUCCESS;
}