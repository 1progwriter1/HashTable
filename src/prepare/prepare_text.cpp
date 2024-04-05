#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "../../MyLibraries/headers/file_func.h"
#include "../../MyLibraries/headers/systemdata.h"

#define WIGHT_FANG "text/wight_fang.txt"
#define PREPARED_TEXT "text/clean_text.txt"

const size_t MAX_WORD_LEN = 128;
const size_t MAX_NUMBER_OF_WORDS = 40000;

int PrepareText(const char *src_file, const char *dst_file);
void cleanWord(char *word, size_t *length);

int main() {

    if (PrepareText(WIGHT_FANG, PREPARED_TEXT) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

int PrepareText(const char *src_file, const char *dst_file) {

    assert(src_file);
    assert(dst_file);

    char *buf = readbuf(src_file);
    if (!buf)   return ERROR;
    char *tmp = buf;

    char word_buf[MAX_WORD_LEN] = "";

    FILE *dst = fopen(dst_file, WRITE);
    if (!dst) return FILE_OPEN_ERROR;

    size_t number_of_words = 0;
    int sym_read = 0;

    while (sscanf(tmp, "%s %n", word_buf, &sym_read) == 1 && number_of_words < MAX_NUMBER_OF_WORDS) {

        tmp += sym_read;
        size_t length = 0;
        cleanWord(word_buf, &length);
        if (length == 0) continue;

        fprintf(dst, "%s\n", word_buf);
        number_of_words += 1;
    }

    fileclose(dst);
    free(buf);

    return SUCCESS;
}

void cleanWord(char *word, size_t *length) {

    assert(word);
    assert(length);

    char tmp[MAX_WORD_LEN] = "";
    size_t index = 0;

    for (size_t i = 0; word[i] != '\0'; i++) {
        if (ispunct((unsigned char) word[i])) continue;
        tmp[index++] = word[i];
        *length += 1;
    }
    tmp[index] = '\0';

    memcpy(word, tmp, *length + 1);
}