#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bitwise_negation.h"

int bitwise_negation(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        const char* format = "bitwise_negation: failed to open file %s";
        char msg[strlen(format) + strlen(filename) + 1];
        sprintf(msg, format, filename);
        perror(msg);
        return 1;
    }
    const size_t buf_len = 128 * 1024;
    char buf[buf_len];
    while (1) {
        const size_t len = fread(buf, sizeof(char), buf_len, file);
        if (ferror(file)) {
            const char* format = "bitwise_negation: failed to read file data %s";
            char msg[strlen(format) + strlen(filename) + 1];
            sprintf(msg, format, filename);
            perror(msg);
            fclose(file);
            return 1;
        }
        if (len <= 0) break;

        for (int i = 0; i < len; i++) buf[i] = ~buf[i];

        if (fseek(file, -(long)len, SEEK_CUR)) {
            const char* format = "bitwise_negation: failed to seek file position %s";
            char msg[strlen(format) + strlen(filename) + 1];
            sprintf(msg, format, filename);
            perror(msg);
            fclose(file);
            return 1;
        }
        if (fwrite(buf, sizeof(char), len, file) != len) {
            const char* format = "bitwise_negation: failed to write file data %s";
            char msg[strlen(format) + strlen(filename) + 1];
            sprintf(msg, format, filename);
            perror(msg);
            fclose(file);
            return 1;
        }
        if (fflush(file) == EOF) {
            const char* format = "bitwise_negation: failed to flush file %s";
            char msg[strlen(format) + strlen(filename) + 1];
            sprintf(msg, format, filename);
            perror(msg);
            fclose(file);
            return 1;
        }

        if (len < buf_len) break;
    }
    if (fclose(file) == EOF) {
        const char* format = "bitwise_negation: failed to close file %s";
        char msg[strlen(format) + strlen(filename) + 1];
        sprintf(msg, format, filename);
        perror(msg);
        return 1;
    }

    return 0;
}
