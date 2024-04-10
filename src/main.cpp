#include <stdio.h>
#include <assert.h>
#include "hash_table/string_list.h"
#include "../../MyLibraries/headers/systemdata.h"
#include "../../MyLibraries/headers/file_func.h"
#include "measure/measure.h"
#include "hash_table/hash_table.h"

int main() {

    HashTableStr table = {};
    if (hashTableStrCtor(&table, hashFuncCRC32) != SUCCESS)
        return ERROR;

    if (loadHashTable(&table, SRC_FILE) != SUCCESS)
        return ERROR;

    hashTableStrDtor(&table);

    return SUCCESS;
}