#include <stdio.h>

#include "xor_codec.h"

static void help() {
    fprintf(stderr,
            "Usage: xor_codec <your_secret> <exist_file> [ <output_file> ]\n"
            "\tyour_secret: the secret\n"
            "\texist_file: input file\n"
            "\toutput_file: output file\n"
            "Example: \n"
            "\tencode: xor_codec your_secret /path/to/file /path/to/output\n"
            "\tdecode: xor_codec your_secret /path/to/file /path/to/output\n"
    );
}

int main(const int argv, const char* argc[]) {
    if (argv < 3) {
        help();
        return 1;
    }
    if (argv == 3) return xor_codec(argc[1], argc[2], argc[2]);

    return xor_codec(argc[1], argc[2], argc[3]);
}
