#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A0.h"

typedef struct S_80173738_0_pre {
    u16 unk_00;
} S_80173738_0_pre;   /* the 0x2 bytes before arg0 in func_80173738, addressed as arg0[-1] */

typedef struct S_80173738_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} S_80173738_0;   /* arg0 in func_80173738 */




typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
} FuncArg1;

M2C_UNK func_8003DB94();
M2C_UNK func_800478B8(void *, s32);
s32 func_800644B8();
s32 func_80064584();
extern s32 D_800814A0[];
extern M2C_UNK D_800DEC70;

void func_80173738(void *arg0, FuncArg1 *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_a0;
    s16 temp_v0;
    s32 temp_lo;
    s32 temp_base;
    s32 temp_delta;
    register void *dst ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

    ((S_80173738_0 *)arg0)->unk_1E = (u16) (((S_80173738_0 *)arg0)->unk_1E - 0x12C);
    ((S_80173738_0 *)arg0)->unk_20 = (u16) (((S_80173738_0 *)arg0)->unk_20 + 2);
    arg1->unk00 = (s32) (((S_80173738_0 *)arg0)->unk_40 + ((s16) ((S_80173738_0 *)arg0)->unk_20 * func_80064584((s16) ((S_80173738_0 *)arg0)->unk_1E) * 0x10));
    temp_lo = (s16) ((S_80173738_0 *)arg0)->unk_20 * func_800644B8((s16) ((S_80173738_0 *)arg0)->unk_1E);
    dst = arg2;
    temp_delta = 0xFFF40000U;
    ASM_KEEP_NV(temp_delta);   /* MATCH pin: keeps a statement from moving across a call/branch */
    temp_base = ((S_80173738_0 *)arg0)->unk_44;
    arg1->unk08 = (s32) (arg1->unk08 + temp_delta);
    arg1->unk04 = (s32) (temp_base + (temp_lo * 0x10));
    func_800478B8(dst, temp_delta);
    if (arg2->unk_14.at00_u16.v & 0x4000) {
        func_8003DB94(arg2, &D_800DEC70, 0);
    }
    temp_a0 = ((S_80173738_0 *)arg0)->unk_1A;
    if (temp_a0 < 0xA) {
        arg2->unk_0C.at00_s8.v = (s8) ((((S_80173738_0 *)arg0)->unk_00 * temp_a0) / 9);
        arg2->unk_0C.at01_s8.v = (s8) ((((S_80173738_0 *)arg0)->unk_01 * ((S_80173738_0 *)arg0)->unk_1A) / 9);
        arg2->unk_0C.at02_s8.v = (s8) ((((S_80173738_0 *)arg0)->unk_02 * ((S_80173738_0 *)arg0)->unk_1A) / 9);
    }
    temp_v0 = (u16) ((S_80173738_0 *)arg0)->unk_1A - 1;
    ((S_80173738_0 *)arg0)->unk_1A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_80173738_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80173738_0_pre *)arg0)[-1].unk_00 | 0x8000);
        ((Rec_D_800814A0 *)D_800814A0)->unk_00 = (s32) (((Rec_D_800814A0 *)D_800814A0)->unk_00 | 0x8000);
    }
}
