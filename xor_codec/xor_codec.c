#include <stdio.h>
#include <string.h>

#include "xor_codec.h"

int xor_codec(const char* secret, const char* input_file, const char* output_file) {
    if (!secret || !input_file || !output_file) {
        fprintf(stderr, "xor_codec: please check parameters\n");
        return 1;
    }
    if (!strlen(secret)) {
        fprintf(stderr, "xor_codec: please check secret parameter\n");
        return 1;
    }

    const size_t len = strlen(secret);
    int cursor = 0;
    unsigned char ch;

    // 简单判断输入输出文件相同。
    if (!strcmp(input_file, output_file)) {
        FILE* f = fopen(input_file, "r+b");
        if (!f) {
            const char* format = "xor_codec: can't open file %s";
            char msg[strlen(input_file) + strlen(format) + 1];
            sprintf(msg, format, input_file);
            perror(msg);
            return 1;
        }

        while (1) {
            ch = fgetc(f);
            if (feof(f)) break;
            if (ferror(f)) {
                const char* format = "xor_codec: failed to read file %s";
                char msg[strlen(input_file) + strlen(format) + 1];
                sprintf(msg, format, input_file);
                perror(msg);
                fclose(f);
                return 1;
            }

            if (len == cursor) cursor = 0;
            ch ^= *(secret + cursor++);
            if (fseek(f, -1, SEEK_CUR)) {
                const char* format = "xor_codec: can't seek file %s";
                char msg[strlen(input_file) + strlen(format) + 1];
                sprintf(msg, format, input_file);
                perror(msg);
                fclose(f);
                return 1;
            }
            fputc(ch, f);
            if (ferror(f)) {
                const char* format = "xor_codec: failed to write file %s";
                char msg[strlen(input_file) + strlen(format) + 1];
                sprintf(msg, format, input_file);
                perror(msg);
                fclose(f);
                return 1;
            }

            if (fflush(f) == EOF) {
                const char* format = "xor_codec: failed to flush file %s";
                char msg[strlen(format) + strlen(input_file) + 1];
                sprintf(msg, format, input_file);
                perror(msg);
                fclose(f);
            }
        }

        if (fclose(f) == EOF) {
            const char* format = "xor_codec: failed to close file %s";
            char msg[strlen(output_file) + strlen(format) + 1];
            sprintf(msg, format, output_file);
            perror(msg);
            return 1;
        }
        return 0;
    }

    FILE* fi = fopen(input_file, "rb");
    if (!fi) {
        const char* format = "xor_codec: failed to open file %s";
        char msg[strlen(input_file) + strlen(format) + 1];
        sprintf(msg, format, input_file);
        perror(msg);
        return 1;
    }
    FILE* fo = fopen(output_file, "wb");
    if (!fo) {
        const char* format = "xor_codec: failed to open file %s";
        char msg[strlen(output_file) + strlen(format) + 1];
        sprintf(msg, format, output_file);
        perror(msg);
        fclose(fi);
        return 1;
    }

    while (1) {
        ch = fgetc(fi);
        if (feof(fi)) break;

        if (ferror(fi)) {
            const char* format = "xor_codec: failed to read file %s";
            char msg[strlen(input_file) + strlen(format) + 1];
            sprintf(msg, format, input_file);
            perror(msg);
            fclose(fi);
            fclose(fo);
            return 1;
        }
        if (len == cursor) cursor = 0;
        ch ^= *(secret + cursor++);
        fputc(ch, fo);
        if (ferror(fo)) {
            const char* format = "xor_codec: failed to write file %s";
            char msg[strlen(output_file) + strlen(format) + 1];
            sprintf(msg, format, output_file);
            perror(msg);
            fclose(fi);
            fclose(fo);
            return 1;
        }
    }

    if (fclose(fi) == EOF) {
        const char* format = "xor_codec: failed to close file %s";
        char msg[strlen(input_file) + strlen(format) + 1];
        sprintf(msg, format, input_file);
        perror(msg);
        return 1;
    }
    if (fclose(fo) == EOF) {
        const char* format = "xor_codec: failed to close file %s";
        char msg[strlen(output_file) + strlen(format) + 1];
        sprintf(msg, format, output_file);
        perror(msg);
        return 1;
    }
    return 0;
}
