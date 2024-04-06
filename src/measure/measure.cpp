#include <stdio.h>
#include <assert.h>
#include "../measure/measure.h"
#include "../../../MyLibraries/headers/systemdata.h"
#include "../hash_table/hash_table.h"
#include "../../../MyLibraries/headers/file_func.h"

int measureHashTable(HashTableStr *table, const char *filename) {

    assert(filename);
    assert(table);

    char *buf = readbuf(SRC_FILE);
    if (!buf)   return ERROR;
    char *tmp = buf;

    char word_buf[MAX_WORD_LEN] = "";

    int sym_read = 0;
    while (sscanf(tmp, "%s %n", word_buf, &sym_read) == 1) {
        tmp += sym_read;
        if (hashTableStrInsert(table, word_buf) != SUCCESS)
            return ERROR;
    }

    FILE *fn = fopen(filename, WRITE);
    if (!fn) return FILE_OPEN_ERROR;

    fprintf(fn, "index,size\n");
    for (size_t i = 0; i < table->size; i++)
        fprintf(fn, "%lu, %lu\n", i, table->lists[i].size);

    free(buf);
    fclose(fn);

    return SUCCESS;
}