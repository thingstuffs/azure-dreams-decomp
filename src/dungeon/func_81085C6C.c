#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A2B04();
extern M2C_UNK func_800A56E0();
extern s32 D_8008346C;
extern M2C_UNK D_80170E94;

typedef struct S_8017346C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x12];
    s8 unk_AE;
} S_8017346C_0;   /* arg0 in func_8017346C */

typedef struct S_8017346C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017346C_1;   /* arg2 in func_8017346C */

typedef struct S_8017346C_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017346C_2;   /* arg1 in func_8017346C */

typedef struct S_8017346C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8017346C_3;   /* arg3 in func_8017346C */

void func_8017346C(S_8017346C_0 *arg0, S_8017346C_2 *arg1, S_8017346C_1 *arg2, S_8017346C_3 *arg3) {
    u8 temp_v1;

    temp_v1 = arg0->unk_9B;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return;
        }
        goto block_8;
    }
    if (arg2->unk_14 & 0x8000) {
        arg0->unk_9B = 1U;
        arg2->unk_14 |= 0x6000;
        return;
    }
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    arg0->unk_9B = (u8) (arg0->unk_9B + 1);
block_8:
    if (((arg2->unk_04 == 5) && (arg2->unk_14 & 0x1000)) || (arg2->unk_14 & 0x8000)) {
        func_800A56E0(0x803);
    }
    if (arg2->unk_14 & 0xE000) {
        arg0->unk_AE = 1;
        arg3->unk_14 = (s32) (arg3->unk_14 | 0x40000000);
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        arg0->unk_8C = &D_80170E94;
        D_8008346C = 0;
    }
}
