#include <stdio.h>
#include <string.h>

#include "xor_codec.h"

int xor_codec(const char *secret, const char *input_file, const char *output_file) {
    if (!secret || !input_file || !output_file) {
        printf("xor_codec: please check parameters\n\n");
        return 1;
    }

    const size_t len = strlen(secret);

    // 输入输出文件相同。
    if (!strcmp(input_file, output_file)) {
        FILE *f = fopen(input_file, "r+b");
        if (!f) {
            printf("xor_codec: can't open file %s\n", input_file);
            return 1;
        }
    } else {

    }
    FILE *fi, *fo;
    int cursor = 0;
    if (secret == NULL || !*secret) return 1;
    if ((fi = fopen(input_file, "rb"))) {
        if ((fo = fopen(output_file, "wb"))) {
            int ch;
            while ((ch = getc(fi)) != EOF) {
                if (len == cursor) cursor = 0;
                ch ^= *(secret + cursor++);
                putc(ch, fo);
            }
            fclose(fo);
        } else {
            printf("open file fail: %s\n", input_file);
            return 1;
        }
        fclose(fi);
    } else {
        return 1;
    }

    printf("%s\n", "RUN OK");
    return 0;
}
