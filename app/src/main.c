/*
 * Главный модуль программы.
 * Осуществляет парсинг аргументов командной строки и вызов библиотечных функций.
 * Зубехин Никита
 * МК-101
 */

#include <stdio.h>
#include <stdlib.h>
#include "replace.h"
#include "hex_parser.h"

void print_usage(const char* prog_name) {
    fprintf(stderr, "Usage: %s <input_file> <output_file> <pattern_hex> <replacement_hex>\n",
            prog_name);
    fprintf(stderr, "Example: %s in.txt out.txt 6164 3132333435 "
                    "(replace 'ad' with '12345')\n", prog_name);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        print_usage(argv[0]);
        return 1;
    }

    const char* in_path = argv[1];
    const char* out_path = argv[2];
    const char* pattern_hex = argv[3];
    const char* replacement_hex = argv[4];

    unsigned char* pattern = NULL;
    unsigned char* replacement = NULL;

    int pattern_len = hex_to_bytes(pattern_hex, &pattern);
    if (pattern_len < 0) {
        fprintf(stderr, "Error: Invalid pattern hex string.\n");
        return 1;
    }

    int replacement_len = hex_to_bytes(replacement_hex, &replacement);
    if (replacement_len < 0) {
        fprintf(stderr, "Error: Invalid replacement hex string.\n");
        free(pattern);
        return 1;
    }

    int result = replace_in_file(in_path, out_path, pattern, pattern_len,
                                 replacement, replacement_len);

    free(pattern);
    free(replacement);

    if (result != 0) {
        fprintf(stderr, "Error during file processing.\n");
        return 1;
    }

    printf("Replacement completed successfully.\n");
    return 0;
}