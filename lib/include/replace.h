/*
 * Модуль замены байтовых последовательностей в файле.
 * Использует кольцевой буфер.
 * Зубехин Никита
 * МК-101
 */

#ifndef REPLACE_H
#define REPLACE_H

#include <stddef.h>

#ifndef N
#define N 1024
#endif


int replace_in_file(const char* in_path, const char* out_path,
                    const unsigned char* pattern, size_t pattern_len,
                    const unsigned char* replacement, size_t replacement_len);

#endif