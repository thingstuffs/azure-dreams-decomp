#ifndef TOWN_MAP_BODY_H
#define TOWN_MAP_BODY_H

#include "common.h"
#include "records/Rec_D_80081FDC.h"

/* Town map control bodies created by town_map_set (pool flags 0x11).
 * The node header supplies the separate position and sprite pointers. */
typedef union TownMapHalf {
    s16 as_s16;
    u16 as_u16;
} TownMapHalf;

typedef struct TownMapBody {
    /* 0x00 */ Rec_D_80081FDC *context;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ void *window_callback;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ u16 unk_40;
    /* 0x42 */ u16 unk_42;
    /* 0x44 */ u8 pad_44[0x1C];
    /* 0x60 */ u16 unk_60;
    /* 0x62 */ u8 pad_62[2];
    /* 0x64 */ TownMapHalf timer;
    /* 0x66 */ s16 type_id;
    /* 0x68 */ void *update;
    /* 0x6C */ void *next_update;
    /* 0x70 */ u8 pad_70[4];
    /* 0x74 */ s32 selection;
    /* 0x78 */ s32 entry_count;
    /* 0x7C */ u8 *entries;
    /* 0x80 */ u8 pad_80[0x54];
} TownMapBody;

#endif
