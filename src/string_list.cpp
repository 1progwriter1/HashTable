#include <stdio.h>
#include <assert.h>
#include "string_list.h"
#include <string.h>

static int listsArraysVerify(ListsArrays *arrays);
static int listsArraysResizeUp(ListsArrays *arrays);

int listsArraysCtor(ListsArrays *arrays) {

    assert(arrays);

    arrays->data = (char **)  calloc (LIST_INIT_SIZE, sizeof(char *));
    arrays->next = (size_t *) calloc (LIST_INIT_SIZE, sizeof(size_t));
    arrays->prev = (size_t *) calloc (LIST_INIT_SIZE, sizeof(size_t));

    if (!arrays->data || !arrays->next || !arrays->prev) {

        free(arrays->data);
        free(arrays->next);
        free(arrays->prev);
        return NO_MEMORY;
    }

    arrays->free = 1;
    arrays->number_of_elements = 0;
    arrays->size = LIST_INIT_SIZE;

    arrays->next[0] = 0;
    arrays->next[arrays->size - 1] = 0;
    arrays->data[0] = NULL;

    for (size_t i = 1; i < arrays->size - 1; i++) {
        arrays->data[i] = NULL;
        arrays->next[i] = i + 1;
        arrays->prev[i] = 0;
    }


    return SUCCESS;
}

int listStrInsertAfter(ListStr *lst, char *str, size_t index, ListsArrays *arrays) {

    assert(lst);
    assert(str);
    assert(arrays);

    if (listsArraysVerify(arrays) != SUCCESS)
        return ERROR;

    if (arrays->free == 0)
        if (listsArraysResizeUp(arrays) != SUCCESS)
            return ERROR;

    size_t free_index = arrays->free;
    arrays->free = arrays->next[free_index];

    if (lst->size == 0)
        lst->head = free_index;
    if (index == lst->tail)
        lst->tail = free_index;

    arrays->next[free_index] = arrays->next[index];
    arrays->prev[free_index] = index;
    arrays->next[index] = free_index;

    size_t len_of_str = strlen(str);
    char *tmp = (char *) calloc (len_of_str + 1, sizeof(char));
    if (!tmp)   return ERROR;

    arrays->data[free_index] = tmp;
    memcpy(arrays->data[free_index], str, (len_of_str + 1) * sizeof(char));
    lst->size++;

    return SUCCESS;
}

void listsArraysDtor(ListsArrays *arrays) {

    assert(arrays);

    free(arrays->data);
    free(arrays->next);
    free(arrays->prev);

    arrays->data = NULL;
    arrays->next = NULL;
    arrays->prev = NULL;

    arrays->number_of_elements = 0;
    arrays->size = 0;
    arrays->free = 0;
}

static int listsArraysResizeUp(ListsArrays *arrays) {

    assert(arrays);

    if (listsArraysVerify(arrays) != SUCCESS)
        return ERROR;

    size_t old_size = arrays->size;
    arrays->size *= RESIZE_COEFF;

    char  **tmp_data = (char **)  realloc (arrays->data, arrays->size * sizeof(size_t));
    size_t *tmp_next = (size_t *) realloc (arrays->next, arrays->size * sizeof(size_t));
    size_t *tmp_prev = (size_t *) realloc (arrays->prev, arrays->size * sizeof(size_t));

    if (!tmp_data || !tmp_next || !tmp_prev) {
        free(tmp_data);
        free(tmp_next);
        free(tmp_prev);
        printf(RED "arrays of lists error: " END_OF_COLOR "data increase failed\n");
        return NO_MEMORY;
    }

    arrays->data = tmp_data;
    arrays->next = tmp_next;
    arrays->prev = tmp_prev;

    arrays->free = old_size;
    arrays->next[arrays->size - 1] = 0;

    for (size_t i = old_size; i < arrays->size - 1; i++) {
        arrays->data[i] = NULL;
        arrays->prev[i] = 0;
        arrays->next[i] = i + 1;
    }

    return SUCCESS;
}

static int listsArraysVerify(ListsArrays *arrays) {

    assert(arrays);

    bool error = false;
    if (!arrays->data || !arrays->next || !arrays->prev) {
        printf(RED "arrays of lists error: " END_OF_COLOR "null pointer\n");
        error = true;
    }
    if (arrays->number_of_elements >= arrays->size) {
        printf(RED "arrays of lists error: " END_OF_COLOR "incorrect size of number or elements\n");
        error = true;
    }
    if (arrays->free >= arrays->size) {
        printf(RED "arrays of lists error: " END_OF_COLOR "incorrect free index or size\n");
        error = true;
    }

    if (error)  return ERROR;
    return SUCCESS;
}