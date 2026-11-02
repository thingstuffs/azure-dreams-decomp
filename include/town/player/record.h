#ifndef TOWN_PLAYER_RECORD_H
#define TOWN_PLAYER_RECORD_H

#include "common.h"

/* initialize_scene_for_mode clears a 0x88-byte node buffer: its 0x20-byte
 * ObjectNodeHeader precedes this 0x68-byte body. Position and sprite storage
 * are supplied separately through the header. */
typedef union TownPlayerHalf {
    s16 as_s16;
    u16 as_u16;
} TownPlayerHalf;

typedef struct TownPlayerRecord {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ u8 pad_08[2];
    /* 0x0A */ TownPlayerHalf timer;
    /* 0x0C */ u8 pad_0C[2];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ TownPlayerHalf unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u8 pad_14[2];
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u8 pad_1A[2];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ u8 pad_20[0xC];
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ u8 pad_34[2];
    /* 0x36 */ s16 target_x;
    /* 0x38 */ s16 target_y;
    /* 0x3A */ u8 pad_3A[4];
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ s32 slot;
    /* 0x44 */ void *unk_44;
    /* 0x48 */ u8 pad_48[0x20];
} TownPlayerRecord;

#endif
