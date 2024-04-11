#ifndef LIST_FUNCTIONS
#define LIST_FUNCTIONS

#include <stdio.h>
#include "../../../MyLibraries/headers/systemdata.h"
#include "immintrin.h"

const size_t LIST_INIT_SIZE = 64;
const size_t RESIZE_COEFF = 2;

union Word {
    char str[32];
    __m256i packed;
};

struct ListNode {
    Word word;
    size_t number;
};

struct ListStr {
    size_t size;
    size_t head;
    size_t tail;
};

struct ListsArrays {
    ListNode *data;
    size_t *next;
    size_t *prev;
    size_t size;
    size_t number_of_elements;
    size_t free;
};

int listsArraysCtor(ListsArrays *arrays);
void listsArraysDtor(ListsArrays *arrays);

int listStrInsertAfter(ListStr *lst, Word str, size_t index, ListsArrays *arrays);

#endif