#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_80024C90(void) __attribute__((noreturn));
extern void func_80024D74(void) __attribute__((noreturn));
extern void func_80024FD8();
extern void func_800254C4();
extern void func_800478B8();
extern s32 func_800644B8();
extern s16 D_800257CC;
extern s16 D_800257CE;
extern s32 D_800814A0;

void func_80024B98(void *arg0, void *arg1, void *arg2) {
    s16 state;
    s32 damage;
    u16 v;

    D_800257CE++;
    state = FIELD(arg0, s16, 0xA);
    if (state != 2) {
        if (state == 0) {
            v = FIELD(arg0, u16, 0x1E) - 1;
            FIELD(arg0, u16, 0x1E) = v;
            if ((s16)v <= 0) {
                FIELD(arg0, u16, 0xA)++;
                goto advance;
            }
        } else {
advance:
            v = FIELD(arg0, u16, 0x1C) + 1;
            FIELD(arg0, u16, 0x1C) = v;
            if ((s16)v >= 0x41) {
                FIELD(arg0, u16, 0xA) = 2;
                func_80024C90();
                return;
            }
            goto common;
        }
    } else {
        FIELD(arg2, s32, 0xC) += 0xFFFBFBFC;
        if (FIELD(arg2, u8, 0xC) < 4) {
            D_800257CC--;
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
            func_80024D74();
            return;
        }
common:
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) += 0x10000;
        if (FIELD(arg1, s16, 0xA) > FIELD(arg0, s16, 0x14))
            FIELD(arg1, s16, 0xA) = FIELD(arg0, s16, 0x14);
        damage = func_800644B8((s16)FIELD(arg0, u16, 0x1C) << 6);
        FIELD(arg2, s32, 0xC) += 0x20202;
        FIELD(arg2, u16, 0x1E) -= damage >> 5;
        if (FIELD(arg2, u8, 0xC) >= 0x41)
            FIELD(arg2, s32, 0xC) = 0x404040;
        func_800478B8(arg2);
        if (!(FIELD(arg0, u16, 0x1C) & 0x1F))
            func_80024FD8(arg1, FIELD(arg0, s16, 0x14), FIELD(arg0, s16, 0x24));
        if (!(FIELD(arg0, u16, 0x1C) & 3))
            func_800254C4(arg1, (FIELD(arg0, s16, 0x24) << 24) >> 16, 0x10, 0);
    }
}

/* MECHANISM: The 0x20 frame follows from holding the three argument bases in s0/s2/s1.
   Restored state=2 and D_800814A0 RMW stores close both tail paths and the four-word cascade.
   Split call-result liveness, reversed compare operands, and a signed shift pair fix scheduling/lh. */
