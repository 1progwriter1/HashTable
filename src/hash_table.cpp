#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#include "../../MyLibraries/headers/systemdata.h"

#define HASH_TABLE_HEAD table->lists[insert_index].head
#define HASH_TABLE_TAIL table->lists[insert_index].tail

int hashTableStrCtor(HashTableStr *table, size_t (*hashFunc)(char *, size_t)) {

    assert(table);
    assert(*hashFunc);

    if (listsArraysCtor(&table->arrays) != SUCCESS)
        return ERROR;

    table->lists = (ListStr *) calloc (HASH_TABLE_SIZE, sizeof(ListStr));
    if (!table->lists) {
        listsArraysDtor(&table->arrays);
        return NO_MEMORY;
    }

    table->size = HASH_TABLE_SIZE;
    table->num_of_elements = 0;
    table->hashFunc = hashFunc;

    return SUCCESS;
}

void hashTableStrDtor(HashTableStr *table) {

    assert(table);

    listsArraysDtor(&table->arrays);
    free(table->lists);
    table->lists = NULL;

    table->size = 0;
    table->num_of_elements = 0;
}

int hashTableStrInsert(HashTableStr *table, char *str) {

    assert(table);
    assert(str);

    size_t insert_index = table->hashFunc(str, HASH_TABLE_SIZE);
    if (insert_index >= table->size) {
        printf(RED "hash_table error: " END_OF_COLOR "incorrect insert_index received\n");
        return ERROR;
    }

    if (isInserted(str, &table->lists[insert_index], &table->arrays)) return SUCCESS;

    if (listStrInsertAfter(&table->lists[insert_index], str, HASH_TABLE_TAIL, &table->arrays) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

bool isInserted(char *str, ListStr *lst, ListsArrays *arrays) {

    assert(str);
    assert(lst);
    assert(arrays);

    size_t cur_index = lst->head;
    if (!arrays->data[cur_index])   return false;

    while (true) {
        if (strcmp(arrays->data[cur_index], str) == 0)  return true;
        if (cur_index == lst->tail) break;
        cur_index = arrays->next[cur_index];
    }

    return false;
}

size_t hashFuncZero(char *str, size_t size) {

    assert(str);

    return 0 % size;
}

size_t hashFuncLetterASCII(char *str, size_t size) {

    assert(str);

    return (size_t) str[0] % size;
}

size_t hashFuncLength(char *str, size_t size) {

    assert(str);

    return strlen(str) % size;
}

size_t hashFuncSumASCII(char *str, size_t size) {

    assert(str);

    size_t ascii_sum = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        ascii_sum += (size_t) str[i];
    }

    return ascii_sum % size;
}

size_t hashFuncCycleShiftRight(char *str, size_t size) {

    assert(str);

    size_t hash = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        hash = myCycleShiftRight(hash) ^ (size_t) str[i];
    }

    return hash % size;
}

size_t hashFuncCycleShiftLeft(char *str, size_t size) {

    assert(str);

    size_t hash = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        hash = myCycleShiftLeft(hash) ^ (size_t) str[i];
    }

    return hash % size;
}

size_t hashFuncDjb2(char *str, size_t size) {

    assert(str);

    size_t hash = 5381;

    for (size_t i = 0; str[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (size_t) str[i];
    }

    return hash % size;
}

size_t myCycleShiftLeft(size_t num) {

    return (num >> (sizeof(size_t) - 1)) | (num << 1);
}

size_t myCycleShiftRight(size_t num) {

    return (num << (sizeof(size_t) - 1)) | (num >> 1);
}