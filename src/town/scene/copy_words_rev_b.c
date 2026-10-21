#include "common.h"

/* Copies count integers from src to dst in forward order. */
void copy_forward_word_span(int *dst, int *src, int count) {
    while (count != 0) {
        *dst = *src;
        src++;
        count--;
        dst++;
    }
}
