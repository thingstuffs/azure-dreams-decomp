#include "common.h"

extern u8 *D_800E3D7C;

s32 func_800C7FFC(u8 *arg0) {
    s32 i;
    u32 mask;
    unsigned long base;
    unsigned long page;
    unsigned long slot;
    u8 *object;

    if (*(u32 *)(arg0 + 0x14) & 0x4000) {
        page = 0x800E0000;
        ASM_KEEP(page);   /* MATCH pin: retail basic-block layout depends on it */
        i = 1;
        base = (unsigned long)*(u8 **)(page + 0x3D7C);
        mask = 0x20000000;
        slot = base + 4;
        while (i >= 0) {
            object = *(u8 **)(slot + 0xAC);
            if (object != 0 && (*(u32 *)(object + 0x54) & mask)) {
                return 1;
            }
            i--;
            slot -= 4;
        }
        return 0;
    }

    slot = *(u32 *)(arg0 + 0x54);
    arg0 = (u8 *)0x20000000;
    slot &= (u32)arg0;
    if (!slot) {
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        return 0;
    }
    return 1;
}

/* MECHANISM: The conditional tail call keeps the function frameless and returns zero in its jump slot.
   Holding the 0x800E0000 page splits the global load into retail's branch-slot lui, li a0, then lw.
   Natural loop locals preserve the a0 counter, a1 mask, v1 slot base, and exact two-edge CFG. */
