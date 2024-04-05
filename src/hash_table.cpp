#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#include "../MyLibraries/headers/systemdata.h"

#define HASH_TABLE_HEAD table->lists[insert_index].head
#define HASH_TABLE_TAIL table->lists[insert_index].tail

int hashTableStrCtor(HashTableStr *table) {

    assert(table);

    if (listsArraysCtor(&table->arrays) != SUCCESS)
        return ERROR;

    table->lists = (ListStr *) calloc (HASH_TABLE_INIT_SIZE, sizeof(ListStr));
    if (!table->lists) {
        listsArraysDtor(&table->arrays);
        return NO_MEMORY;
    }

    table->size = HASH_TABLE_INIT_SIZE;
    table->num_of_elements = 0;

    return SUCCESS;
}

void hashTableStrDtor(HashTableStr *table) {

    assert(table);

    listsArraysDtor(&table->arrays);
    free(table->lists);
    table->lists = NULL;

    table->size = 0;
    table->num_of_elements - 0;
}

int hashTableStrInsert(HashTableStr *table, char *str) {

    assert(table);
    assert(str);

    size_t insert_index = table->hash_func();
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

size_t hashFuncZero() {
    return 0;
}