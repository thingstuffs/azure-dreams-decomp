#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800374F4(u32);
extern void *func_8003FC64(s32);
extern s32 func_800A2674(void);
extern u8 D_800A2690[9];

void *func_800A25CC(s32 arg0)
{
    s32 temp_s0;
    s16 temp_v0;
    void *temp_s1;
    void *temp_s2;

    temp_s2 = func_8003FC64(0x136);
    if (temp_s2 == 0) {
        return 0;
    }
    FIELD(temp_s2, void *, 0x10) = D_800A2690;
    temp_s1 = temp_s2 + 0x20;
    temp_v0 = func_800374F4(0xB4) + 0x3C;
    FIELD(temp_s1, s16, 4) = temp_v0;
    FIELD(temp_s1, s16, 6) = temp_v0;
    FIELD(temp_s1, s32, 0x10) = (func_800374F4(0x28) & 0xFFFF) + 0x80;
    FIELD(temp_s1, s32, 0x14) = arg0;
    temp_s0 = func_800374F4(0x40);
    FIELD(temp_s1, s16, 8) = temp_s0 + func_800374F4(0x40) - 0x40;
    FIELD(temp_s1, s16, 0xA) = func_800374F4(0x40);
    FIELD(temp_s1, s16, 0xC) = func_800374F4(0x40);
    ASM_MEM_BARRIER();
    func_800A2674();
    return temp_s2;
}

/* MECHANISM: Natural long-lived locals produce the retail 0x20 frame and s0/s1/s2 save roles.
   ASM_MEM_BARRIER keeps the final halfword store before the tail call; removing the stale
   disabled noreturn prototype lets SHAPE-C emit j func_800A2674 with move v0,s2 in its slot. */
