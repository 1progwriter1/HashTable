#ifndef MEASURE_FUNCTIONS
#define MEASURE_FUNCTIONS

#include <stdio.h>
#include "hash_table.h"

#define SRC_FILE "clean_text.txt"

const size_t MAX_WORD_LEN = 128;

enum HashTableMode {
    ZeroHash = 0,
    LetterASCII = 1,
    Length = 2,
    SumASCII = 3,
    CycleShiftLeft = 4,
    CycleShiftRight = 5,
    MyDjb2 = 6,
};

int measureHashTable(HashTableStr *table, const char *filename);
int PrepareText(const char *src_file, const char *dst_file);

#endif