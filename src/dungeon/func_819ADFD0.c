#include "common.h"

/* 16 bytes copied as four packed words (the animation table stride is 0x16, so entries are only 2-aligned). */
typedef struct {
    s32 words[4];
} __attribute__((packed)) PackedWords4;

/* One 0x16-byte animation entry (the table row func_8002590C selects by index; see func_800257D0's callers). */
typedef struct {
    PackedWords4 words;
    s16 field_10;
    s8 field_12;        /* widened to dst->field_14 */
    s8 field_13;        /* widened to dst->field_18 */
    s8 field_14;        /* widened to dst->field_1C */
} AnimEntry;

/* The 0x20-byte current-frame block the entry is expanded into. */
typedef struct {
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
