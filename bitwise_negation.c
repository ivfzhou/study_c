#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bitwise_negation.h"

void bitwise_negation(const char* filename) {
    printf("process file %s\n", filename);
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        const char* msg_part1 = "failed to open file ";
        char msg[strlen(msg_part1) + strlen(filename) + 1];
        sprintf(msg, "%s%s", msg_part1, filename);
        perror(msg);
        exit(EXIT_FAILURE);
    }
    const size_t buf_len = 128 * 1024;
    char buf[buf_len];
    while (1) {
        const size_t len = fread(buf, sizeof(char), buf_len, file);
        if (ferror(file)) {
            perror("failed to read file data");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        if (len <= 0) break;

        for (int i = 0; i < len; i++) buf[i] = ~buf[i];

        if (fseek(file, -(long)len, SEEK_CUR)) {
            perror("failed to seek file position");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        if (fwrite(buf, sizeof(char), len, file) != len) {
            perror("failed to write file data");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        if (fflush(file) == EOF) {
            perror("failed to flush file");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (len < buf_len) break;
    }
    if (fclose(file) == EOF) {
        perror("failed to close file");
        exit(EXIT_FAILURE);
    }
    printf("process successfully\n");
}
