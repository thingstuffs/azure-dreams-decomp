#include "common.h"

extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s32 func_8009A540(u16, s16, s16, s16);
extern s16 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;

s32 func_80018304(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register s32 raw_x ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 raw_y ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 flags;
    s16 x;
    s16 y;
    s16 z;
    s16 index;
    s16 height;
    s32 px;
    s32 py;

    raw_x = arg0;
    raw_y = arg1;
    z = arg2 - 0x20;
    x = raw_x;
    y = raw_y;
    if ((func_8009A540(arg3 & 0xFFFF, x, y, z) << 16) == 0) {
        goto failure;
    }

    index = arg3;
    if ((func_8009A350(x, y, index, &flags) << 16) == 0) {
        goto failure;
    }

    px = raw_x + ((u16 *)&D_8006CCD8)[index];
    py = raw_y + ((u16 *)&D_8006CCE8)[index];
    if (flags & 0x8400) {
        goto failure;
    }

    height = func_800BCB04(
        (((px << 16) >> 10) + 0x20) & 0xFFE0,
        (((py << 16) >> 10) + 0x20) & 0xFFE0,
        z);
    if (height >= 0x200) {
        goto failure;
    }
    if ((s16)arg2 >= height) {
        return 2;
    }
    if ((height - (s16)arg2) < 0x21) {
        return 1;
    }
failure:
    return 0;
}

/* MECHANISM: Raw s32 inputs plus distinct normalized s16 lifetimes produce the
   0x38 frame; raw_x/raw_y pins to s3/s4 close the three-role coloring cycle.
   The sp+0x10 u16 output and recovered local 0x80018438 epilogue fix the CFG. */
