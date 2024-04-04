#ifndef LIST_FUNCTIONS
#define LIST_FUNCTIONS

#include <stdio.h>
#include "../MyLibraries/headers/systemdata.h"

const size_t LIST_INIT_SIZE = 64;
const size_t RESIZE_COEFF = 2;

struct ListStr {
};

struct ListsArrays {
    char **data;
    size_t *next;
    size_t *prev;
    size_t size;
    size_t number_of_elements;
    size_t free;
};

int ListsArraysCtor(ListsArrays *arrays);
void ListsArraysDtor(ListsArrays *arrays);


#endif