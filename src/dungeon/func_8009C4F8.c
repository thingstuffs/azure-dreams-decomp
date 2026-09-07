#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s16 func_80042900(void *, s32);
extern void func_800A1D34(void);
extern s32 D_800835E8[];
extern u8 *D_800E3D7C[];
s32 func_800A1C58(void *a) {
    s16 r = 0;
    s32 *table;
    u8 *entry;
    u8 *global_page;
    u8 index;
    u32 offset;

    if (F(a,s8,0x13) < 0) {
        func_800A1D34();
        return 0;
    }
    if (F(a,u8,0x11) >= 0x63) {
        func_800A1D34();
        return 0;
    }
    if ((func_80042900(a, 10) << 16) != 0) {
        func_800A1D34();
        return 0;
    }
    if (F(a,u32,0x1C) & 0x80000) {
        return r;
    }
    if (F(a,u8,0x13) == 0) {
        global_page = (u8 *)0x800E0000;
        ASM_KEEP(global_page);   /* MATCH pin: retail basic-block layout depends on it */
        if (F(F(global_page,u8 *,0x3D7C),u8,0x9A) == 0x22) {
            return r;
        }
    }
    if (F(a,u32,0x1C) & 0x228) {
        return r;
    }
    table = (s32 *)0x80080000;
    ASM_KEEP(table);   /* MATCH pin: load-bearing for the whole function shape */
    index = F(a,u8,0x11);
    offset = index << 2;
    table = (s32 *)((u8 *)table + 0x35E8);
    entry = (u8 *)(offset + (u32)table);
    ASM_KEEP(entry);   /* MATCH pin: load-bearing for the whole function shape */
    if (*(u32 *)entry <= F(a,u32,0x18)) {
        r++;
    }
    return r;
}
/* MECHANISM: Nested early-zero CFG yields the 0x20 s0/s1 frame and LEAD22 tail-zero pair.
   Split 0x800E/0x8008 page bases fill both load delays; s16 r preserves return shifts.
   Guarded v1/v0 roles plus scaled-index-first integer addition fix the final addu ordering. */
