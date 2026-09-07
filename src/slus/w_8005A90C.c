#include "common.h"

typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} S_80086A40;

extern S_80086A40 D_80086A40[16];
extern s32 D_8007382C[3]; /* size > 8: forced hi/lo, no $gp */

extern void func_8005A1D0(s32);
extern s32 func_80059F8C(s32, s32);
extern s32 func_8005ECA0(s32);
extern s32 func_8005EC40(s32, u32);

s32 func_8005A90C(s32 arg0, s32 arg1, s32 arg2, s16 arg3)
{
    s16 i;
    s16 sel;
    s32 idx;
    S_80086A40 *slot;
    s32 ret;
    s32 a2c;

    D_8007382C[0] = 0;
    i = 0;
    sel = arg3;
    if (sel == -1) {
        do {
            if (D_80086A40[i].marker == -1) {
                goto found;
            }
            i++;
        } while (i < 16);
        return -1;
    }
    i = sel;
    if (D_80086A40[i].marker != -1) {
        func_8005A1D0(D_80086A40[i].unk10);
    }
found:
    idx = i;
    slot = &D_80086A40[idx];

    slot->unk14 = arg2;
    ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
    slot->marker = i;
    slot->unk04 = arg0;
    slot->unk08 = arg2;
    a2c = arg2;
    ASM_KEEP_NV(a2c);   /* MATCH pin: slus-diff */
    ret = arg1;
    slot->unk18 = 0x7F;
    slot->unk1B = 0x40;
    slot->unk10 = ret;
    ret = func_80059F8C(ret, a2c);
    slot->unk10 = ret;
    if (ret == -1) {
        return -1;
    }
    arg1 = func_8005ECA0(ret);
    if (func_8005EC40(arg0, slot->unk14) != slot->unk14) {
        return -1;
    }
    slot->unk0C = arg0;
    ret = arg1;
    slot->unk10 = ret;
    return idx;
}
