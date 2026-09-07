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

typedef struct {
    /* 0x00 */ u8 pad00[0xC];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ u8 pad10[2];
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u8 pad14[4];
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
} Sound;

extern S_80086A40 D_80086A40[16];
extern s32 D_8007382C[3]; /* size > 8: forced hi/lo, no $gp */
extern void func_8005A1D0(s32);
extern s32 func_80059E94(s32);

s32 func_8005A608(Sound *arg0, s16 arg1)
{
    s16 i;
    s16 sel;
    s32 idx;
    S_80086A40 *slot;
    s32 base;
    s32 len;

    D_8007382C[0] = 0;
    i = 0;
    sel = arg1;
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
    slot->marker = i;
    slot->unk04 = (s32)arg0;
    slot->unk08 = (arg0->unk12 << 9) + 0xA20;
    slot->unk14 = arg0->unk0C - slot->unk08;
    slot->unk18 = arg0->unk18;
    slot->unk1B = arg0->unk19;
    slot->unk10 = func_80059E94(slot->unk14);
    if (slot->unk10 == -1) {
        return -1;
    }
    return idx;
}
