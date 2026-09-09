#include "common.h"

extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_800BCB04();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

s32 func_800A4688(s32 arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4) {
    u16 value;
    u16 x_offset;
    u16 y_offset;
    register u32 x ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 y ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 shifted_sector;
    s32 sector_arg;
    s32 call_x;
    s32 call_y;
    s32 sector;
    s32 height;
    s32 z;
    s32 x_sum;
    s32 y_sum;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    x = (u32)(arg0 & 0xFFFF) >> 6;
    y = (u32)(arg1 & 0xFFFF) >> 6;
    shifted_sector = arg3 >> 9;
    sector_arg = shifted_sector & 7;

    if (arg4 != 0) {
        return 0;
    }
    ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    call_x = x;
    call_y = y;
    ASM_KEEP(call_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(call_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    sector = sector_arg;
    ASM_KEEP(sector);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if ((func_8009A350(call_x, call_y, sector_arg, &value) << 16) == 0) {
        return 0;
    }

    z = (s16)(arg2 - 0x20);
    x_offset = D_8006CCD8[sector];
    y_offset = D_8006CCE8[sector];
    x_sum = x_offset + x;
    y_sum = y_offset + y;
    ASM_USE2(x_sum, y_sum);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    height = func_800BCB04(
        ((((x_sum) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        ((((y_sum) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        z);
    result = 0x02000000 < (height << 16);
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    value = height;
    return result;
}

/* MECHANISM: A 0x30 frame holds s1=arg2, s3=x, s2=y, and s0=sector across calls.
   Post-guard keeps preserve shifted a3/a2 until pinned a0/a1 call arguments are ready,
   then a kept s0 move fixes the call order; paired sums and tail-store order close the body. */
