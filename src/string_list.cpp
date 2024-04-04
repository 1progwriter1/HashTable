#include <stdio.h>
#include <assert.h>
#include "string_list.h"

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

    for (size_t i = 0; i < arrays->size; i++) {
        if (i == 0) {
            arrays->prev[i] = 0;
            arrays->next[i] = 0;
        }
        else {
            if (i == arrays->size - 1)
                arrays->next[i] = 0;
            else
                arrays->next[i] = i + 1;
            arrays->prev[i] = 0;
        }
    }

    arrays->data[0] = NULL;

    arrays->free = 1;
    arrays->number_of_elements = 0;
    arrays->size = LIST_INIT_SIZE;

    return SUCCESS;
}

int listStrInsertAfter(ListStr *lst, char *str, size_t index, ListsArrays *arrays) {

    assert(lst);
    assert(str);
    assert(arrays);

    if (listsArraysVerify(arrays) != SUCCESS)
        return ERROR;

    size_t free_index = arrays->free;
    arrays->free = arrays->next[free_index];
    arrays->next[index] = arrays->next[index];
    arrays->prev[index] = index;
    arrays->next[index] = free_index;

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

    arrays->size *= RESIZE_COEFF;
    char **tmp = (char **) realloc (arrays->data, sizeof(char *) * arrays->size);
    if (!tmp)   return NO_MEMORY;
    arrays->data = tmp;

    size_t *ind_tmp = (size_t *) realloc (arrays->next, sizeof(size_t) * arrays->size);
    if (!ind_tmp)   return NO_MEMORY;
    arrays->next = ind_tmp;

    ind_tmp = (size_t *) realloc (arrays->prev, sizeof(size_t) * arrays->size);
    if (!ind_tmp)   return NO_MEMORY;
    arrays->prev = ind_tmp;

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
        printf(RED "arrays of lists error: " END_OF_COLOR "incorrect size of number of elements\n");
        error = true;
    }

    if (error)  return ERROR;
    return SUCCESS;
}