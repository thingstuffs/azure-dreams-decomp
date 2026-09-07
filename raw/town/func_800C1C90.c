#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64(u32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);

extern u8 D_80046398[];
extern u8 D_800BF1C8[];
extern u8 D_800D232C[];
extern s32 D_800D2344[3];
extern s32 D_800814A0[3];

void func_800BF3F0(void *arg0)
{
    void *temp_a0;
    void *temp_a1;
    void *temp_v0;
    void *temp_v1;
    s32 value;
    u32 color;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        func_8004491C(temp_v0, D_80046398);
        color = 0x00808080U;
        
        FIELD(temp_v0, void *, 0x10) = D_800BF1C8;
        temp_v1 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_v1, s16, 0x1C) = 0x1000;
        FIELD(temp_v1, s16, 0x1E) = 0x1000;
        FIELD(temp_v1, s16, 0x20) = 0x1000;
        FIELD(temp_v1, u32, 0xC) = color;
        temp_a0 = temp_v0 + 0x20;
        FIELD(temp_v1, s16, 0x1A) = 0;
        FIELD(temp_v1, s32, 8) = 0x4A;
        temp_a1 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a1, s32, 0) = 0x02C00000;
        FIELD(temp_a1, s32, 4) = 0x02300000;
        value = D_800D2344[0];
        FIELD(temp_a1, s32, 8) = 0xFFC00000;
        FIELD(temp_a0, s32, 0x48) = value;
        func_8008F074(temp_a0, temp_a1, D_800D232C);
    }
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

/* MECHANISM: The 0x20 frame holds arg0 in s1 and the allocated object in s0.
   Loading D_800D2344 before the final buffer store creates retail's a0 handoff
   and schedules the global lui/lw pair before the 0xFFC00000 store. */
