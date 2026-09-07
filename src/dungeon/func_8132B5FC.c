#include "common.h"

typedef struct S_80172DFC_0_pre {
    u16 unk_00;
} S_80172DFC_0_pre;   /* the 0x2 bytes before arg0 in func_80172DFC, addressed as arg0[-1] */

typedef struct S_80172DFC_0 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x3E];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
} S_80172DFC_0;   /* arg0 in func_80172DFC */

typedef struct S_80172DFC_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172DFC_1;   /* arg1 in func_80172DFC */

typedef struct S_80172DFC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80172DFC_2;   /* arg2 in func_80172DFC */



extern void func_800478B8(void *);
extern s32 D_800814A0[3];

void func_80172DFC(void *arg0, S_80172DFC_1 *arg1, S_80172DFC_2 *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;

    ((S_80172DFC_0 *)arg0)->unk_58 = ((S_80172DFC_0 *)arg0)->unk_58 + ((S_80172DFC_0 *)arg0)->unk_64;
    ((S_80172DFC_0 *)arg0)->unk_5C = ((S_80172DFC_0 *)arg0)->unk_5C + ((S_80172DFC_0 *)arg0)->unk_68;
    ((S_80172DFC_0 *)arg0)->unk_60 = ((S_80172DFC_0 *)arg0)->unk_60 + ((S_80172DFC_0 *)arg0)->unk_6C;
    arg1->unk_00 = arg1->unk_00 + ((S_80172DFC_0 *)arg0)->unk_58;
    arg1->unk_04 = arg1->unk_04 + ((S_80172DFC_0 *)arg0)->unk_5C;
    arg1->unk_08 = arg1->unk_08 + ((S_80172DFC_0 *)arg0)->unk_60;
    temp_v0 = ((S_80172DFC_0 *)arg0)->unk_18 + 1;
    ((S_80172DFC_0 *)arg0)->unk_18 = temp_v0;
    if (!(temp_v0 & 1)) {
        func_800478B8(arg2);
    }
    arg2->unk_1C = arg2->unk_1C + 0x28;
    arg2->unk_1E = arg2->unk_1E + 0x28;
    temp_v0_2 = ((S_80172DFC_0 *)arg0)->unk_16 - 1;
    ((S_80172DFC_0 *)arg0)->unk_16 = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        ((S_80172DFC_0_pre *)arg0)[-1].unk_00 = ((S_80172DFC_0_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
    if (arg2->unk_14 & 0x8000) {
        ((S_80172DFC_0_pre *)arg0)[-1].unk_00 = ((S_80172DFC_0_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
