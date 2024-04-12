#include <stdio.h>
#include <assert.h>
#include "hash_table/string_list.h"
#include "../../MyLibraries/headers/systemdata.h"
#include "../../MyLibraries/headers/file_func.h"
#include "measure/measure.h"
#include "hash_table/hash_table.h"
#include <string.h>
#include <time.h>

const size_t NUMBER_OF_PASSES = 50000;

int main(const int argc, const char *argv[]) {

    // if (argc < 2)   return ERROR;

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hashFuncRolAsm) != SUCCESS)
        return ERROR;

    #ifdef MEASURE
    unsigned int start = __rdtsc();
    #endif

    clock_t begin = clock();

    if (loadHashTable(&table, SRC_FILE) != SUCCESS)
        return ERROR;

    size_t found = 0;
    for (size_t j = 0; j < NUMBER_OF_PASSES; j++) {

        for (size_t i = 0; i < table.arrays.size; i++) {

            size_t insert_index = table.hashFunc(table.arrays.data[i].word.str, table.size);

            if (isInserted(table.arrays.data[i].word, &table.lists[insert_index], &table.arrays))
                found++;
        }
    }

    #ifdef MEASURE
    unsigned int end = _rdtsc();
    printf("main: %u\n", end - start);
    #endif

    hashTableStrDtor(&table);

    printf("%lu\n", found);

    clock_t finish = clock();

    printf("%f\n", (double) (finish - begin) / CLOCKS_PER_SEC);

    return SUCCESS;
}