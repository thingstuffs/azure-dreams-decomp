#include "common.h"

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80083160[];

s32 func_8009A2B8(s16 arg0, s16 arg1, s32 arg2) {
    s32 x;
    s32 y;
    s32 value;
    u8 *base;
    u8 *entry;

    base = D_80083160;
    ASM_KEEP(base);
    x = arg0 + ((s16 *)D_8006CCD8)[(s16)arg2];
    y = arg1 + ((s16 *)D_8006CCE8)[(s16)arg2];
    x += y << *(s16 *)(base + 0x1F0);
    entry = *(u8 **)(base + 0x1DC) + x * 6;
    value = *(u16 *)(entry + 4) & 0xF320;
    if (value != 0) {
        value = 1;
        goto done;
    }
    value = *(u16 *)entry;
    if (value != 0) {
        value = 0;
        goto done;
    }
    value = 1;
done:
    ASM_SCHED_BARRIER();
    return value;
}

/* MECHANISM: Frameless leaf; ASM_KEEP holds D_80083160 at words 0-1.
   Symbolic s16 indexing reproduces the interleaved argument normalization.
   One v0 result lifetime plus an epilogue barrier prevents tail duplication. */
