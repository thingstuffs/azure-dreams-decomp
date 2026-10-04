#include "common.h"

typedef struct S_80810220_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    void * unk_04;
    u8 pad_08[0x4C];
    union { s16 s; u16 u; } unk_54;   /* accessed as both */
} S_80810220_0;   /* control_data in func_80810220 */

typedef struct S_80810220_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x6];
    u16 unk_20;
    s16 unk_22;
} S_80810220_1;   /* child in func_80810220 */

typedef struct S_80810220_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_80810220_2;   /* output_data in func_80810220 */

typedef struct S_80810220_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80810220_3;   /* value_data in func_80810220 */

typedef struct S_80810220_4 {
    u8 pad_00[0x22];
    s16 unk_22;
} S_80810220_4;   /* ((S_80810220_0 *)control_data)->unk_04 in func_80810220 */

extern s32 func_80252550(void *, void *);
extern u32 D_80012BCC[4];
extern u8 D_805300C4[0x100];
extern u32 D_80530100[];
__asm__(".set D_80530100, 0x80530100");

void func_8052AE20(S_80810220_0 *control_data, S_80810220_3 *value_data, S_80810220_2 *output_data) {
    S_80810220_1 *child;
    s16 called;
    s16 state;
    u16 flags;

    child = control_data->unk_04;
    called = 0;

    if (child->unk_18 == 0) {
        control_data->unk_00 = 0;
    }

    if (D_80012BCC[0] >= 1000U) {
        if (func_80252550(D_805300C4, value_data) != 0) {
            called = 1;
        } else {
            output_data->unk_08 = D_80530100[control_data->unk_54.s + 3];
        }
    }

    state = control_data->unk_00;
    switch (state) {
    case 0:
    {
        s32 value;
        value = value_data->unk_08 - 0x80000;
        value_data->unk_08 = value;
        if (value <= 0) {
            value_data->unk_08 = 0;
            output_data->unk_0C = 0x808080;
            control_data->unk_00 = 1;
        }
        return;
    }

    case 1:
    {
        s32 called_v0;
        called_v0 = called;
        if (called_v0 != 0 && ((S_80810220_4 *)(control_data->unk_04))->unk_22 == 3) {
            child->unk_20 |= 1;
            output_data->unk_08 = D_80530100[control_data->unk_54.s + 6];
            child->unk_22 = control_data->unk_54.u;
        }
        if (child->unk_22 != 3) {
            if (((S_80810220_4 *)(control_data->unk_04))->unk_22 ==
                control_data->unk_54.s) {
                control_data->unk_00 = 3;
                return;
            }
            control_data->unk_00 = 2;
        }
        return;
    }

    case 2:
    {
        s32 value;
        value = value_data->unk_08 + 0x80000;
        value_data->unk_08 = value;
        if (value > 0x3FFFFF) {
            value_data->unk_08 = 0x400000;
        }
        return;
    }

    case 3:
        flags = child->unk_20;
        if (flags & 1) {
            child->unk_20 = flags | 1;
            output_data->unk_08 = D_80530100[control_data->unk_54.s + 6];
        }
        return;

    default:
        return;
    }
}
