#ifndef HASH_TABLE_FUNCTIONS
#define HASH_TABLE_FUNCTIONS

#include <stdio.h>
#include "string_list.h"

const size_t HASH_TABLE_SIZE = 2003;
const size_t NUMBER_OF_HASH_FUNC = 8;

struct HashTableStr {
    size_t (*hashFunc)(char *, size_t);
    ListsArrays arrays;
    ListStr *lists;
    size_t size;
    size_t num_of_elements;
};

int hashTableStrCtor(HashTableStr *table, size_t (*hashFunc)(char *, size_t));
void hashTableStrDtor(HashTableStr *table);

int hashTableStrInsert(HashTableStr *table, char *str);
bool isInserted(char *str, ListStr *lst, ListsArrays *arrays);

size_t hashFuncZero(char *str, size_t size);
size_t hashFuncLetterASCII(char *str, size_t size);
size_t hashFuncLength(char *str, size_t size);
size_t hashFuncSumASCII(char *str, size_t size);
size_t hashFuncRol(char *str, size_t size);
size_t hashFuncRor(char *str, size_t size);
size_t hashFuncDjb2(char *str, size_t size);
size_t hashFuncCRC32(char *str, size_t size);

size_t myRol(size_t num);
size_t myRor(size_t num);

#endif