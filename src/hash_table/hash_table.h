#ifndef HASH_TABLE_FUNCTIONS
#define HASH_TABLE_FUNCTIONS

// #define MEASURE

#include <stdio.h>
#include "string_list.h"

const size_t HASH_TABLE_SIZE = 101;
const size_t NUMBER_OF_HASH_FUNC = 8;
const size_t MAX_WORD_LEN = 32;

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
bool isInserted(Word str, ListStr *lst, ListsArrays *arrays);
int loadHashTable(HashTableStr *table, const char *filename);

int myStrcmp(Word a, Word b);
size_t hashFuncCRC32fast(char *str, size_t size);
size_t hashFuncRolAsm(char *str, size_t size);

// extern "C" size_t hashFuncSumASCIIAsm(char *str, size_t size);

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