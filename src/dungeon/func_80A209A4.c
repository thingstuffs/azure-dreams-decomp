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

void func_801741A4(Func80A209A4Data *arg0) {
    Func80A209A4Data *data = arg0;
    u16 count;

    
    data->fieldC += data->field10;
    data->field10 += data->field14;
    data->field14 += 0xFFFF4000;
    data->field8 += 0x10000;
    count = data->field18 - 1;
    data->field18 = count;
    if ((count << 16) <= 0) {
        *(u16 *)((u8 *)data - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; the guarded $a2 data pin reproduces the entry copy and base lifetime.
   Direct compound member updates preserve retail load order and induce its v0/v1 copy pseudos. */
