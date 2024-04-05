#ifndef HASH_TABLE_FUNCTIONS
#define HASH_TABLE_FUNCTIONS

#include <stdio.h>
#include "string_list.h"

const size_t HASH_TABLE_INIT_SIZE = 101;

struct HashTableStr {
    size_t (*hash_func)();
    ListsArrays arrays;
    ListStr *lists;
    size_t size;
    size_t num_of_elements;
};

int hashTableStrCtor(HashTableStr *table);
void hashTableStrDtor(HashTableStr *table);

int hashTableStrInsert(HashTableStr *table, char *str);
bool isInserted(char *str, ListStr *lst, ListsArrays *arrays);

#endif