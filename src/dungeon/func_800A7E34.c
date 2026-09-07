#include "common.h"

typedef struct S_800AD594_0 {
    u8 pad_00[0x13];
    union { s8 s; u8 u; } unk_13;   /* accessed as both */
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x4];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 pad_26[0x2E];
    s32 unk_54;
    u8 pad_58[0xE];
    u8 unk_66;
} S_800AD594_0;   /* arg0 in func_800AD594 */

typedef struct S_800AD594_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AD594_1;   /* counterBase in func_800AD594 */



extern s32 func_80042900(void *, s32);
extern void func_80094E34(void);
extern s32 D_80012090[];
extern s32 D_80083460;

void func_800AD594(S_800AD594_0 *arg0, s32 arg1) {
    s32 amount;
    s32 reduction;
    s32 one;
    u8 initialLevel;
    u8 currentLevel;
    u8 *counterBase;

    reduction = arg1;
    if (arg0->unk_13.s > 0) {
        amount = arg0->unk_24.at00.v;
        initialLevel = arg0->unk_24.at01.v;
        if ((func_80042900(arg0, 0x20) << 16) != 0) {
            reduction = 0;
        } else if (arg0->unk_54 & 0x100) {
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
        currentLevel = arg0->unk_66;
        arg0->unk_24.at00.v = (u16)amount;
        if (currentLevel < arg0->unk_24.at01.v) {
            arg0->unk_24.at01.v = currentLevel;
            arg0->unk_24.at00u.v = 0xFF;
        }
        if (arg0->unk_24.at01.v == 0) {
            s32 dungeonMode;

            one = 1;
            
            dungeonMode = *(s32 *)0x80012090;
            if ((dungeonMode == one) &&
                ((arg0->unk_13.u == 2) ||
                 (arg0->unk_13.u == 0x39))) {
                arg0->unk_24.at01.v = dungeonMode;
                return;
            }
            if (arg0->unk_1C & 0x80000) {
                func_80094E34();
            }
            if (initialLevel != 0) {
                counterBase = (u8 *)&D_80083460;
                ((S_800AD594_1 *)counterBase)->unk_0A =
                    ((S_800AD594_1 *)counterBase)->unk_0A + 1;
            }
        }
    }
}

/* MECHANISM: Recovered the three true-space jumps as local joins and kept arg0 in both
   two-argument calls, yielding the retail 0x28 frame and s1/s2/s0 lifetimes.
   ASM_KEEP(one) restores the delay-slot li/load nop; the fixed-address state read
   coalesces its page and value in a0, while D_80083460 uses a named tail base. */
