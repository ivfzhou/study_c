#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bitwise_negation.h"

void bitwise_negation(const char *filename) {
    puts("开始处理");
    FILE *file = fopen(filename, "rb+");
    if (!file) {
        perror(strcat("fopen error ", filename));
        exit(EXIT_FAILURE);
    }
    const size_t buf_len = 32 * 1024;
    char buf[buf_len];
    while (1) {
        size_t len = fread(buf, sizeof(char), buf_len, file);
        if (ferror(file)) {
            perror("fread error");
            exit(EXIT_FAILURE);
        }
        if (len <= 0) break;

        for (int i = 0; i < len; i++) buf[i] = (char) ~buf[i];

        if (fseek(file, (long) -len, SEEK_CUR)) {
            perror("fseek error");
            exit(EXIT_FAILURE);
        }
        if (fwrite(buf, sizeof(char), len, file) != len) {
            perror("fwrite error");
            exit(EXIT_FAILURE);
        }
        if (ferror(file)) {
            perror("fwrite error");
            exit(EXIT_FAILURE);
        }

        if (len < buf_len) break;
    }
    if (fclose(file) == EOF) {
        perror(strcat("fclose error ", filename));
        exit(EXIT_FAILURE);
    }
    puts("结束处理");
}
