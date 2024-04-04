#include <stdio.h>
#include "src/string_list.h"
#include "../MyLibraries/headers/systemdata.h"

int main() {

    ListsArrays arrays = {};
    if (listsArraysCtor(&arrays) != SUCCESS)
        return ERROR;

    char str[] = "hello world";

    ListStr lst = {};
    for (size_t i = 0; i < 100; i++)
        if (listStrInsertAfter(&lst, str, lst.tail, &arrays) != SUCCESS)
            return ERROR;

    for (size_t i = 0; i < arrays.size; i++) {
        if (!arrays.data[i])
            fprintf(stderr, "%3lu) NULL\n", i);
        else
            fprintf(stderr, "%3lu) %s (%lu %lu)\n", i, arrays.data[i], arrays.free, arrays.prev[i]);
    }
    return SUCCESS;
}