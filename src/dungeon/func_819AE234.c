#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_flags.h"


/* Fade RGB toward black and set flags when red falls below eight. */
void func_80025A34(void *owner, s32 unused, void *color_data) {
    u8 red;
    u8 green;
    u8 blue;

    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
    red = *((u8 *)color_data + 0xC);
    green = *((u8 *)color_data + 0xD);
    *((u8 *)color_data + 0xC) = red - (red >> 1);
    blue = *((u8 *)color_data + 0xE);
    *((u8 *)color_data + 0xD) = green - (green >> 1);
    *((u8 *)color_data + 0xE) = blue - (blue >> 1);
    if (*((u8 *)color_data + 0xC) < 8) {
        *((u16 *)owner - 1) |= 0x8000;
        *(u32 *)((u8 *)(&objectFlagBlock)) |= 0x8000;
    }
}

