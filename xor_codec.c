#include <stdio.h>
#include <string.h>

#include "xor_codec.h"

void xor_codec_help() {
    printf("%s",
           "xor codec:\nUsage: <bin> <key> <input> <output>\n\tkey: the secret\n\tinput: input file\n\toutput: output file\n");
    printf("%s", "Example: \n\tencode: xor_codec ismykey afile tofile\n\tdecode: xor_codec ismykey tofile afile\n");
}

int xor_codec(const char *key, const char *input, const char *output) {
    if (!key || !input || !output) {
        xor_codec_help();
        return 1;
    }
    FILE *fi, *fo;
    int cursor = 0;
    size_t len = strlen(key);
    if (key == NULL || !*key) return 1;
    if ((fi = fopen(input, "rb"))) {
        if ((fo = fopen(output, "wb"))) {
            int ch;
            while ((ch = getc(fi)) != EOF) {
                if (len == cursor) cursor = 0;
                ch ^= *(key + cursor++);
                putc(ch, fo);
            }
            fclose(fo);
        } else {
            printf("open file fail: %s\n", input);
            xor_codec_help();
            return 1;
        }
        fclose(fi);
    } else {
        xor_codec_help();
        return 1;
    }

    printf("%s\n", "RUN OK");
    return 0;
}
