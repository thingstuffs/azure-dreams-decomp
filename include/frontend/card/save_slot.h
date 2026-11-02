#ifndef FRONTEND_CARD_SAVE_SLOT_H
#define FRONTEND_CARD_SAVE_SLOT_H
#include "common.h"
/* Cached save headers use a 128-byte stride. Retail reads words and the
 * halfword at +8; the complete table allocation bound is unestablished. */
typedef union CardSaveSlot {
    s32 words[32];
    s16 halfwords[64];
    u8 bytes[128];
    struct {
        u8 pad_00[8];
        s32 unk_08;
        u8 pad_0C[0x10];
        u32 play_frames;
        u8 pad_20[4];
        s32 unk_24;
        u8 pad_28[4];
        s32 unk_2C;
        s32 icon_flags;
        s32 unk_34;
    } fields;
} CardSaveSlot;
#endif
