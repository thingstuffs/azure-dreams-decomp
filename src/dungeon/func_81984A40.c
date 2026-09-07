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
} Source81984A40;

typedef struct {
    PackedWords4 words;
    s16 field_10;
    s16 pad_12;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} Dest81984A40;

void func_81984A40(Dest81984A40 *dst, Source81984A40 *src)
{
    s32 field_10;

    dst->words = src->words;
    field_10 = src->field_10;
    dst->field_10 = field_10;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}
