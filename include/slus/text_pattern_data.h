#ifndef SLUS_TEXT_PATTERN_DATA_H
#define SLUS_TEXT_PATTERN_DATA_H

#include "common.h"

/* Resident pattern at 0x80080B70; the next link symbol is 0x80080B80. */
typedef struct StringTailFillPattern {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 pad[13];
} StringTailFillPattern;

extern StringTailFillPattern string_tail_fill_pattern;

#endif
