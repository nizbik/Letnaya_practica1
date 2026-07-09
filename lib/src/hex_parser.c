/*
 * Реализация парсера HEX-строк.
 * Зубехин Никита
 * МК-101
 */

#include "hex_parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int hex_to_bytes(const char* hex_str, unsigned char** out_bytes) {
    if (!hex_str || !out_bytes) {
        return -1;
    }

    size_t len = strlen(hex_str);
    if (len % 2 != 0) {
        return -1; // Длина HEX-строки должна быть чётной 
    }

    size_t byte_len = len / 2;
    *out_bytes = (unsigned char*)malloc(byte_len);
    if (!*out_bytes) {
        return -1;
    }

    for (size_t i = 0; i < byte_len; ++i) {
        unsigned int byte;
        if (sscanf(hex_str + 2 * i, "%2x", &byte) != 1) {
            free(*out_bytes);
            *out_bytes = NULL;
            return -1;
        }
        (*out_bytes)[i] = (unsigned char)byte;
    }

    return (int)byte_len;
}