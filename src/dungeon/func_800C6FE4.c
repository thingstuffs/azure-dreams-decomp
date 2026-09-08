#include "common.h"

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))

extern s32 D_800814A0;

void func_800CC744(void *arg0, void *arg1, void *arg2) {
    s16 temp_a1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 delta;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;

    if (S16(arg0, 0) == 0) {
        temp_v1 = U8(arg2, 0xC);
        U8(arg2, 0xC) = temp_v1 + ((0xE0 - temp_v1) / S16(arg0, 2));
        temp_v1_2 = U8(arg2, 0xD);
        temp_a1 = S16(arg0, 2);
        temp_v0 = U8(arg2, 0xE);
        U8(arg2, 0xD) = temp_v1_2 + ((0xE0 - temp_v1_2) / temp_a1);
        delta = (0xE0 - temp_v0) / S16(arg0, 2);
        U8(arg2, 0xE) = temp_v0 + delta;
        temp_v0_2 = U16(arg0, 2) - 1;
        S16(arg0, 2) = temp_v0_2;
        if ((temp_v0_2 << 16) <= 0) {
            S16(arg0, 2) = 0x10;
            U16(arg0, 0)++;
            return;
        }
    } else {
        U8(arg2, 0xC) = U8(arg2, 0xC) - (U8(arg2, 0xC) / S16(arg0, 2));
        U8(arg2, 0xD) = U8(arg2, 0xD) - (U8(arg2, 0xD) / S16(arg0, 2));
        U8(arg2, 0xE) = U8(arg2, 0xE) - (U8(arg2, 0xE) / S16(arg0, 2));
        temp_v0_3 = U16(arg0, 2) - 1;
        S16(arg0, 2) = temp_v0_3;
        if ((temp_v0_3 << 16) <= 0) {
            U16(arg0, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}

/* MECHANISM: The retail function is frameless and save-free; natural locals preserve its byte/halfword widths.
   The cdk-G0 lineage supplies the retail tail-jump/store schedule.
   Direct scalar D_800814A0 access removes an address addiu and restores the load-delay nop. */
