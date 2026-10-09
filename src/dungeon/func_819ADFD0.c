#include "common.h"

typedef struct {
    s32 words[4];
} __attribute__((packed)) PackedWords4;

typedef struct {
    PackedWords4 words;
    s16 field_10;
    s8 field_12;
    s8 field_13;
    s8 field_14;
} Source800257D0;

typedef struct {
    PackedWords4 words;
    s16 field_10;
    s16 pad_12;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} Dest800257D0;

/* Copies the source record, sign-extending its three byte fields into destination words. */
void func_800257D0(Dest800257D0 *dst, Source800257D0 *src)
{
    s32 sourceHalfword;

    dst->words = src->words;
    sourceHalfword = src->field_10;
    dst->field_10 = sourceHalfword;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}
