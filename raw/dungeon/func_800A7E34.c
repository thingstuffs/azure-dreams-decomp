#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80042900(void *, s32);
extern void func_80094E34(void);
extern s32 D_80012090[];
extern s32 D_80083460;

void func_800AD594(void *arg0, s32 arg1) {
    s32 amount;
    s32 reduction;
    s32 one;
    u8 initialLevel;
    u8 currentLevel;
    u8 *counterBase;

    reduction = arg1;
    if (FIELD(arg0, s8, 0x13) > 0) {
        amount = FIELD(arg0, u16, 0x24);
        initialLevel = FIELD(arg0, u8, 0x25);
        if ((func_80042900(arg0, 0x20) << 16) != 0) {
            reduction = 0;
        } else if (FIELD(arg0, s32, 0x54) & 0x100) {
            reduction = (reduction + 1) >> 1;
        }
        if ((func_80042900(arg0, 0xF) << 16) != 0) {
            reduction *= 2;
        }
        amount -= reduction;
        if (amount < 0) {
            amount = 0;
        } else if (amount > 0x10000) {
            amount = 0xFFFF;
        }
        currentLevel = FIELD(arg0, u8, 0x66);
        FIELD(arg0, u16, 0x24) = (u16)amount;
        if (currentLevel < FIELD(arg0, u8, 0x25)) {
            FIELD(arg0, u8, 0x25) = currentLevel;
            FIELD(arg0, u8, 0x24) = 0xFF;
        }
        if (FIELD(arg0, u8, 0x25) == 0) {
            s32 dungeonMode;

            one = 1;
            
            dungeonMode = *(s32 *)0x80012090;
            if ((dungeonMode == one) &&
                ((FIELD(arg0, u8, 0x13) == 2) ||
                 (FIELD(arg0, u8, 0x13) == 0x39))) {
                FIELD(arg0, u8, 0x25) = dungeonMode;
                return;
            }
            if (FIELD(arg0, s32, 0x1C) & 0x80000) {
                func_80094E34();
            }
            if (initialLevel != 0) {
                counterBase = (u8 *)&D_80083460;
                FIELD(counterBase, u16, 0xA) =
                    FIELD(counterBase, u16, 0xA) + 1;
            }
        }
    }
}

/* MECHANISM: Recovered the three true-space jumps as local joins and kept arg0 in both
   two-argument calls, yielding the retail 0x28 frame and s1/s2/s0 lifetimes.
   ASM_KEEP(one) restores the delay-slot li/load nop; the fixed-address state read
   coalesces its page and value in a0, while D_80083460 uses a named tail base. */
