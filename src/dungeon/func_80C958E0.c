#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801730E0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801730E0_0;   /* arg0 in func_801730E0 */





extern s32 D_80083460[3];
extern u8 D_8017102C[];
extern M2C_UNK D_801752E4;
extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_800B66C8(void *);
extern void func_800419EC(s32, s32);

void func_801730E0(S_801730E0_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3) {
    s16 temp_v1;
    u16 temp_v0;
    s16 var_v1;
    s32 *var_a0;
    u8 *var_v0;

    temp_v1 = arg0->unk_9B;
    if (temp_v1 == 1)
        goto case_1;
    if (temp_v1 < 2) {
        if (temp_v1 == 0)
            goto case_0;
        goto epilogue;
    }
    if (temp_v1 == 2)
        goto case_2;
    goto epilogue;

case_0:
        func_800AD4D0(arg3);
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800B66C8(arg1);
        func_800B66C8(arg1);
        func_800B66C8(arg1);
        func_800B66C8(arg1);
        func_800419EC(4, 6);
        arg0->unk_9B = arg0->unk_9B + 1;
        if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
            if (arg2->unk_14.at00_u16.v & 0x8000) {
                arg0->unk_96.s = 0;
                arg0->unk_9B = 2;
                goto epilogue;
            }
            var_v1 = -1U;
            if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228)
                var_v1 = 8;
            arg0->unk_96.s = var_v1;
            goto block_15;
        }
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800AAA54(arg0, arg1, arg2, &D_801752E4);
        goto epilogue;

case_1:
block_15:
        if (arg0->unk_96.u > 0) {
            temp_v0 = arg0->unk_96.s - 1;
            arg0->unk_96.s = temp_v0;
            goto block_20;
        }
        if (arg2->unk_14.at00_u16.v & 0x6000)
            arg0->unk_96.s = 0;
block_20:
        if (arg0->unk_96.u != 0)
            goto epilogue;
        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            arg1->unk_14.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
            arg1->unk_0C.as_s32 = 0;
            func_800AAA54(arg0, arg1, arg2, &D_801752E4);
            goto epilogue;
        }
        func_800419EC(1, 1);
        arg0->unk_96.s = 8;
        arg0->unk_9B = arg0->unk_9B + 1;
        goto epilogue;

case_2:
        temp_v0 = arg0->unk_96.s - 1;
        arg0->unk_96.s = temp_v0;
        if ((temp_v0 << 0x10) > 0)
            goto epilogue;
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        var_a0 = D_80083460;
        if (var_a0[4] == (arg3 - 0x20)) {
            var_a0[4] = var_a0[4] & 0x7FFFFFFF;
        }
        var_v0 = D_8017102C;
        arg0->unk_8C = var_v0;
        goto epilogue;

epilogue:
    return;
}
