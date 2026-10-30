#ifndef TOWN_SHOP_GRID_MENU_H
#define TOWN_SHOP_GRID_MENU_H

#include "common.h"

/* Body state shared by grid-menu navigation and its countdown dispatcher. */
typedef struct GridMenuObject {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ s32 selected_index;
    /* 0x08 */ s32 entry_count;
    /* 0x0C */ s32 selected_row;
    /* 0x10 */ s32 field_10;
    /* 0x14 */ s32 repeat_ticks;
    /* 0x18 */ s32 field_18;
    /* 0x1C */ s32 dispatch_mode;
    /* 0x20 */ s32 entry_base;
    /* 0x24 */ u8 pad_24[4];
    /* 0x28 */ s32 subrecord;
    /* 0x2C */ s32 field_2C;
} GridMenuObject;

#endif
