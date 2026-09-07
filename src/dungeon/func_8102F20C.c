#include "common.h"
#include "m2c_compat.h"

typedef struct S_8102F20C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F20C_0;   /* arg1 in func_8102F20C */

typedef struct S_8102F20C_1_pre {
    u16 unk_00;
} S_8102F20C_1_pre;   /* the 0x2 bytes before arg0 in func_8102F20C, addressed as arg0[-1] */

typedef struct S_8102F20C_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    u8 pad_1E[0xA];
    void * unk_28;
} S_8102F20C_1;   /* arg0 in func_8102F20C */

typedef struct S_8102F20C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F20C_2;   /* temp_v1 in func_8102F20C */

typedef struct S_8102F20C_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0xC];
    u16 unk_14;
} S_8102F20C_3;   /* out in func_8102F20C */


typedef struct {
    u16 x0;
    u16 x1;
    u16 x2;
} Stack3;

extern s8 D_800DCECC[];
extern s16 D_80083228[5];
extern s32 D_800814A0[3];
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800478B8(void *, s32);

void func_8102F20C(void *arg0, S_8102F20C_0 *arg1, void *arg2) {
    Stack3 sp10;
    M2C_UNK sp24;
    M2C_UNK sp20;
    M2C_UNK sp18[2];
    s16 temp_s0;
    s32 temp_a1;
    S_8102F20C_2 *temp_v1;
    S_8102F20C_3 *out;

    out = arg2;
    sp10.x0 = arg1->unk_02;
    sp10.x1 = arg1->unk_06;
    sp10.x2 = arg1->unk_0A;
    temp_s0 = func_80065420(&sp10.x0, &sp18, &sp20, &sp24);
    temp_v1 = ((S_8102F20C_1 *)arg0)->unk_28;
    sp10.x0 = temp_v1->unk_02;
    sp10.x1 = temp_v1->unk_06;
    sp10.x2 = temp_v1->unk_0A;
    temp_s0 = temp_s0 - func_80065420(&sp10.x0, &sp18, &sp20, &sp24);
    temp_a1 = D_800DCECC[((s32) (*D_80083228 + ((S_8102F20C_1 *)arg0)->unk_1C + 0x100) >> 9) & 7] * 2;
    temp_s0 = temp_s0 + temp_a1;
    out->unk_14 = (u16) (out->unk_14 & 0xFF7F);
    out->unk_06 = temp_s0;
    func_800478B8(out, temp_a1);
    if (out->unk_14 & 0x6000) {
        ((S_8102F20C_1_pre *)arg0)[-1].unk_00 = (u16) (((S_8102F20C_1_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
