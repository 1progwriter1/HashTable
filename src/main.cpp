#include <stdio.h>
#include <assert.h>
#include "hash_table/string_list.h"
#include "../../MyLibraries/headers/systemdata.h"
#include "../../MyLibraries/headers/file_func.h"
#include "measure/measure.h"
#include "hash_table/hash_table.h"
#include <string.h>

int main() {


    HashTableStr table = {};
    if (hashTableStrCtor(&table, hashFuncZero) != SUCCESS)
        return ERROR;

    #ifdef MEASURE
    unsigned int start = __rdtsc();
    #endif

    if (loadHashTable(&table, SRC_FILE) != SUCCESS)
        return ERROR;

    #ifdef MEASURE
    unsigned int end = _rdtsc();
    printf("main: %u\n", end - start);
    #endif

    hashTableStrDtor(&table);


    return SUCCESS;
}