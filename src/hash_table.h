#ifndef HASH_TABLE_FUNCTIONS
#define HASH_TABLE_FUNCTIONS

#include <stdio.h>
#include "string_list.h"

const size_t HASH_TABLE_INIT_SIZE = 101;

struct HashTable {
    size_t (*hash_func)();
    size_t size;
    ListsArrays arrays;
    ListStr *lists;
};

#endif