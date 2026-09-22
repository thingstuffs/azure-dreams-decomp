#include "common.h"

typedef struct S_808152DC_0_pre {
    u16 unk_00;
} S_808152DC_0_pre;   /* the 0x2 bytes before record in func_808152DC, addressed as record[-1] */

typedef struct S_808152DC_0 {
    u8 pad_00[0x50];
    s16 unk_50;
    u16 unk_52;
} S_808152DC_0;   /* record in func_808152DC */



extern s32 func_80058F88();
extern s32 D_80084D5C;

/* Step the record's two-state timer, raising the finished bit when it runs out. */
void func_808152DC(void *record) {
    s16 state;
    u16 timer;

    state = ((S_808152DC_0 *)record)->unk_50;
    if (state != 0) {
        if (state != 1) {
            return;
        }
        goto active;
    }

    func_80058F88(0x603);
    ((S_808152DC_0 *)record)->unk_50 = (u16)((u16)((S_808152DC_0 *)record)->unk_50 + 1);

active:
    timer = ((S_808152DC_0 *)record)->unk_52 - 1;
    ((S_808152DC_0 *)record)->unk_52 = timer;
    if ((timer << 0x10) <= 0) {
        func_80058F88(0x1603);
        (*(u16 *)((u8 *)record + -2)) = ((S_808152DC_0_pre *)record)[-1].unk_00 | 0x8000;
        D_80084D5C |= 0x8000;
    }
}
