#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"

/* The 0x20-byte current-frame block the entry is expanded into. */
typedef struct FrameState {
    PackedWords4 words;
    s16 field_10;
    s16 pad_12;
    s32 field_14;
    s32 field_18;
    s32 field_1C;
} FrameState;

/* Copies the animation entry, sign-extending its three byte fields into destination words. */
void func_800257D0(FrameState *dst, AnimEntry *src)
{
    s32 halfword;

    dst->words = src->words;
    halfword = src->field_10;
    dst->field_10 = halfword;
    dst->field_14 = src->field_12;
    dst->field_18 = src->field_13;
    dst->field_1C = src->field_14;
}

