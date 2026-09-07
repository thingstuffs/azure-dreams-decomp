#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
    u16 field18;
} Func80A209A4Data;

extern s32 D_800814A0[3];

/* Advance motion and set completion flags when the countdown expires. */
void func_801741A4(Func80A209A4Data *motion) {
    Func80A209A4Data *data = motion;
    u16 ticks_left;

    data->fieldC += data->field10;
    data->field10 += data->field14;
    data->field14 += 0xFFFF4000;
    data->field8 += 0x10000;
    ticks_left = data->field18 - 1;
    data->field18 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        *(u16 *)((u8 *)data - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; the guarded $a2 data pin reproduces the entry copy and base lifetime.
   Direct compound member updates preserve retail load order and induce its v0/v1 copy pseudos. */
