/*
 * Реализация алгоритма замены с использованием кольцевого буфера.
 * Зубехин Никита
 * МК-101
 */

#include "replace.h"
#include <stdio.h>
#include <stdlib.h>

#define BUF_CAPACITY (3 * N)

/* Вспомогательная функция для записи из кольцевого буфера в файл */
static void write_from_circular(FILE* fout, unsigned char* buf,
                                long long abs_start, int len) {
    if (len <= 0) return;
    int pos = abs_start % BUF_CAPACITY;
    int first_part = BUF_CAPACITY - pos;

    if (first_part >= len) {
        fwrite(buf + pos, 1, len, fout);
    } else {
        fwrite(buf + pos, 1, first_part, fout);
        fwrite(buf, 1, len - first_part, fout);
    }
}

static int find_pattern(unsigned char* buf, long long abs_start, int count,
                        const unsigned char* pattern, int pattern_len, int max_offset) {
    for (int i = 0; i <= max_offset; ++i) {
        int match = 1;
        for (int j = 0; j < pattern_len; ++j) {
            if (buf[(abs_start + i + j) % BUF_CAPACITY] != pattern[j]) {
                match = 0;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

int replace_in_file(const char* in_path, const char* out_path,
                    const unsigned char* pattern, size_t pattern_len,
                    const unsigned char* replacement, size_t replacement_len) {
    if (pattern_len == 0) return -1;

    FILE* fin = fopen(in_path, "rb");
    FILE* fout = fopen(out_path, "wb");
    if (!fin || !fout) {
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return -1;
    }

    unsigned char* buf = (unsigned char*)malloc(BUF_CAPACITY);
    if (!buf) {
        fclose(fin);
        fclose(fout);
        return -1;
    }

    long long abs_start = 0;
    int count = 0;

    while (1) {
        int pos = (abs_start + count) % BUF_CAPACITY;
        size_t bytes_read = fread(buf + pos, 1, N, fin);
        count += bytes_read;
        int is_eof = (bytes_read < N);

    
        int safe_limit = count;

        int search_offset = 0;
        while (search_offset <= safe_limit - pattern_len) {
            int max_search = safe_limit - pattern_len;
            int match_offset = find_pattern(buf, abs_start, count,
                                            pattern, pattern_len, max_search);

            if (match_offset == -1) {
                write_from_circular(fout, buf, abs_start + search_offset,
                                    safe_limit - search_offset);
                abs_start += safe_limit;
                count -= safe_limit;
                search_offset = safe_limit;
            } else {
                write_from_circular(fout, buf, abs_start + search_offset,
                                    match_offset - search_offset);
                fwrite(replacement, 1, replacement_len, fout);

                int advance = match_offset - search_offset + pattern_len;
                abs_start += advance;
                count -= advance;
                search_offset += advance;
            }
        }

        if (is_eof) break;
    }

    free(buf);
    fclose(fin);
    fclose(fout);
    return 0;
}