#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK func_8003DB94();
extern M2C_UNK func_800478B8();
extern M2C_UNK D_800F15E4;

typedef struct S_800BC764_0 {
    u8 pad_00[0x68];
    s16 unk_68;
    u8 pad_6A[0x2];
    u16 unk_6C;
} S_800BC764_0;   /* arg0 in func_800BC764 */

typedef struct S_800BC764_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800BC764_1;   /* arg2 in func_800BC764 */

void func_800BC764(S_800BC764_0 *arg0, void *arg1, S_800BC764_1 *arg2) {
    s16 temp_v1;
    u16 temp_v0;

    temp_v1 = arg0->unk_68;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        return;
    }
    if (temp_v1 == 2) {
        goto state_2;
    }
    return;

state_0:
    arg0->unk_6C = 0x3CU;
    arg0->unk_68 = (s16) ((u16) arg0->unk_68 + 1);
state_1:
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        arg0->unk_68 = (s16) ((u16) arg0->unk_68 + 1);
        return;
    }
    return;

state_2:
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        func_8003DB94(arg2, &D_800F15E4, 0);
        arg0->unk_68 = 0;
    }
}

/* MECHANISM: A three-argument ABI holds arg0 in s0 and arg2/a2 in s1, producing
   the retail 0x20 frame and save order. Explicit duplicated noreturn default
   edges preserve case layout and place all three tail calls and delay slots. */
