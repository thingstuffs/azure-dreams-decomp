#ifndef SHARED_ANIMATION_VIEWS_H
#define SHARED_ANIMATION_VIEWS_H
#include "common.h"
/* Byte-matching workaround: retain the packed four-word copy for animation
 * entries with a 0x16 stride and only two-byte alignment. A naturally
 * two-aligned spelling remains a follow-up; this is not a final game layout. */
typedef struct { s32 words[4]; } __attribute__((packed)) PackedWords4;
/* One animation entry; the explicit tail byte preserves its measured stride. */
typedef struct AnimEntry {
    PackedWords4 words;
    s16 field_10;
    s8 field_12; /* widened to dst->field_14 */
    s8 field_13; /* widened to dst->field_18 */
    s8 field_14; /* widened to dst->field_1C */
    u8 pad_15;
} AnimEntry;
typedef struct AnimPlayer {
    s32 entry;
    u8 index; /* signed when compared */
    u8 pad_05[3];
    void *owner;
    u8 pad_0C[8];
    u16 flags; /* 0x4000 while clamped */
} AnimPlayer;
typedef struct AnimOwner { u8 pad_00[0xC]; s32 table; } AnimOwner;

/* Exact access views shared across registered binary consumers. */
/* Leading unsigned frame value divided by the animation rate divisor. */
typedef struct AnimationFrameRate {
    /* 0x00 */ unsigned short value;
} AnimationFrameRate;

#endif
