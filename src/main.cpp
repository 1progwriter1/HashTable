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

    assert(argv);

    FILE *fn = stdout;
    bool custom_file = false;
    if (argc >= 2) {;
        const char *filename = argv[1];
        fn = openFile(filename, APPEND);
        if (!fn)    return ERROR;
        custom_file = true;
    }

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hashFuncCRC32fast) != SUCCESS)
        return ERROR;

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
    printf("%lu\n", found);

    clock_t finish = clock();
    fprintf(fn, "%f\n", (double) (finish - begin) / CLOCKS_PER_SEC);

    hashTableStrDtor(&table);

    if (custom_file) closeFile(fn);

    return SUCCESS;
}