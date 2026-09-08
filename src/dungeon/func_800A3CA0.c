#include "common.h"

extern void func_800A9498(u8 *, s32);
extern u8 D_800DD8E7[9];
extern u8 *D_800E3D7C;

s32 func_800A9400(s32 arg0)
{
    s32 raw = arg0;
    s16 index;
    u8 *tile;
    s32 value;

    ASM_KEEP(raw);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    index = raw;
    tile = D_800DD8E7 + index;
    value = *tile;

    if (*(*(u8 **)(D_800E3D7C + 0x4C) + 1) != 0) {
        if (value == 0x32) {
            func_800A9498(tile, arg0);
            return 7;
        }
        if (value == 0x39) {
            func_800A9498(tile, arg0);
            return 8;
        }
        if (value == 0x40) {
            func_800A9498(tile, arg0);
            return 9;
        }
    } else {
        if (value == 0x32) {
            func_800A9498(tile, arg0);
            return 1;
        }
        if (value == 0x39) {
            func_800A9498(tile, arg0);
            return 2;
        }
        if (value == 0x40) {
            func_800A9498(tile, arg0);
            return 3;
        }
    }

    return (s16)arg0;
}
