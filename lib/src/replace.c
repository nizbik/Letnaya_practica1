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

static int find_pattern(unsigned char* buf, long long start_pos, int count,
                        const unsigned char* pattern, int pattern_len, int max_offset) {
    for (int i = 0; i <= max_offset; ++i) {
        int match = 1;
        for (int j = 0; j < pattern_len; ++j) {
            if (buf[(start_pos + i + j) % BUF_CAPACITY] != pattern[j]) {
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

       
        int safe_limit;
        if (is_eof) {
            safe_limit = abs_start + count;
        } else {
            safe_limit = abs_start + count - (2 * N - 1);
            if (safe_limit < abs_start) safe_limit = abs_start;
        }

       
        int processed = 0;

        while (abs_start + processed < safe_limit) {
            int remaining = safe_limit - abs_start - processed;
            int max_search = remaining - pattern_len;
            if (max_search < 0) max_search = 0;

            int match_offset = find_pattern(buf, abs_start + processed,
                                            count - processed,
                                            pattern, pattern_len, max_search);

            if (match_offset == -1) {

                write_from_circular(fout, buf, abs_start + processed, remaining);
                abs_start += remaining;
                count -= remaining;
                processed = 0;
            } else {
                
                write_from_circular(fout, buf, abs_start + processed, match_offset);
             
                fwrite(replacement, 1, replacement_len, fout);

             
                int advance = match_offset + pattern_len;
                abs_start += advance;
                count -= advance;
                processed = 0; 
            }
        }

        if (is_eof) break;
    }

    free(buf);
    fclose(fin);
    fclose(fout);
    return 0;
}