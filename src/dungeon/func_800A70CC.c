#include "common.h"
#include "m2c_compat.h"

typedef struct EarlyCallData {
    u8 pad0[8];
    s32 value;
} EarlyCallData;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_800E3DA8[2];
s32 func_8003DE58();
s32 func_8004CAE8(s32, s32);
M2C_UNK func_80094E34();
s32 func_8009B88C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AACA4();
M2C_UNK func_8009A21C();
M2C_UNK func_800AA36C();
s16 func_800BCB04();


typedef struct S_800AC82C_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x1C];
    u8 unk_24;
    u8 unk_25;
} S_800AC82C_0;   /* arg2 in func_800AC82C */

typedef struct S_800AC82C_1 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_800AC82C_1;   /* arg0 in func_800AC82C */

typedef struct S_800AC82C_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800AC82C_2_pre;   /* the 0x18 bytes before temp_v0 in func_800AC82C, addressed as temp_v0[-1] */

typedef struct S_800AC82C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    u8 unk_24;
    u8 unk_25;
} S_800AC82C_3;   /* temp_a1 in func_800AC82C */

typedef struct S_800AC82C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800AC82C_4;   /* arg1 in func_800AC82C */

typedef struct S_800AC82C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800AC82C_5;   /* temp_s2 in func_800AC82C */

typedef struct S_800AC82C_6 {
    u8 pad_00[0x2A];
    union { volatile u16 v; s16 n; } unk_2A;   /* accessed as both */
} S_800AC82C_6;   /* temp_v0_5 in func_800AC82C */

typedef struct S_800AC82C_7_pre {
    EarlyCallData * unk_00;
    u8 pad_04[0x10];
} S_800AC82C_7_pre;   /* the 0x14 bytes before (*(void **)((u8 *)arg3 + 0x60)) in func_800AC82C, addressed as (*(void **)((u8 *)arg3 + 0x60))[-1] */

typedef struct S_800AC82C_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_800AC82C_7;   /* (*(void **)((u8 *)arg3 + 0x60)) in func_800AC82C */

s32 func_800AC82C(S_800AC82C_1 *arg0, S_800AC82C_4 *arg1, S_800AC82C_0 *arg2, void *arg3) {
    u16 sp18[3];
    u16 sp20;
    u16 sp22;
    M2C_UNK var_a2;
    s16 temp_v0_3;
    s32 temp_v0_4;
    u16 temp_a0;
    u16 temp_parent_u16;
    s32 temp_a1_2;
    s32 temp_v1_2;
    u16 temp_v0_2;
    s32 temp_v0_6;
    u8 temp_v1;
    u8 temp_x;
    u8 temp_y;
    S_800AC82C_3 *temp_a1;
    S_800AC82C_5 *temp_s2;
    void *temp_v0;
    S_800AC82C_6 *temp_v0_5;

    arg2->unk_06 = 0;
    temp_v1 = arg0->unk_9B;
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return 0;
        }
        goto block_6;
    }
    temp_a1 = ((S_800AC82C_7_pre *)((*(void **)((u8 *)arg3 + 0x60))))[-1].unk_00;
    if (func_8004CAE8(((EarlyCallData *) temp_a1)->value, 0) != 0) {
        arg0->unk_9B = (u8) (arg0->unk_9B + 1);
block_6:
        if ((*(s16 *)((u8 *)arg3 + 0x64)) < 0) {
            func_80094E34();
        }
        if ((*(s8 *)((u8 *)arg3 + 0x6D)) != 0) {
            func_800A9A0C(arg3);
        }
        if ((*(s32 *)((u8 *)arg3 + 0x1C)) & 0x200000) {
            func_800AACA4(arg0, arg1, arg2, arg3);
            return 0;
        }
        temp_v0 = (*(void **)((u8 *)arg3 + 0x60));
        temp_a1 = ((S_800AC82C_2_pre *)temp_v0)[-1].unk_04;
        temp_s2 = ((S_800AC82C_2_pre *)temp_v0)[-1].unk_00;
        arg2->unk_24 = (u8) temp_a1->unk_24;
        arg2->unk_25 = (u8) temp_a1->unk_25;
        if (!((*(s32 *)((u8 *)arg3 + 0x1C)) & 0x80000)) {
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF7);
            temp_v0_2 = ((S_800AC82C_7 *)((*(void **)((u8 *)arg3 + 0x60))))->unk_2A;
            (*(u16 *)((u8 *)arg3 + 0x6A)) = temp_v0_2;
            arg2->unk_24 = (u8) (temp_a1->unk_24 + *(u8 *) &D_8006CCD8[(temp_v0_2 >> 9) & 7]);
            arg2->unk_25 = (u8) (temp_a1->unk_25 + *(u8 *) &D_8006CCE8[((u16) (*(u16 *)((u8 *)arg3 + 0x6A)) >> 9) & 7]);
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            temp_v0_3 = func_800BCB04(arg1->unk_02, arg1->unk_06, (s16) ((*(u16 *)((u8 *)arg3 + 0x88)) - 0x20));
            if (temp_v0_3 < 0x200) {
                arg0->unk_92 = 0;
                (*(u16 *)((u8 *)arg3 + 0x88)) = (u16) temp_v0_3;
            }
            if ((func_8009B88C(arg3, arg2->unk_24, arg2->unk_25, &sp20, &sp22) << 0x10) != 0) {
                arg2->unk_24 = sp20;
                arg2->unk_25 = sp22;
                func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
                temp_v0_4 = (*(s32 *)((u8 *)arg3 + 0x1C)) | 0x40000000;
                (*(s32 *)((u8 *)arg3 + 0x1C)) = temp_v0_4;
                temp_x = arg2->unk_24;
                temp_y = arg2->unk_25;
                var_a2 = 0x3000;
                if (temp_v0_4 & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A21C(temp_x, temp_y, var_a2);
                (*(s8 *)((u8 *)arg3 + 0x71)) = 0;
                return 1;
            }
            func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
            func_800AA36C(arg0, arg1, arg2, arg3);
            return 0;
        }
        if (func_8003DE58(temp_a1->unk_08, temp_a1, sp18, 0) != 0) {
            arg1->unk_02 = (u16) ((u16) *D_800E3DA8 + (temp_s2->unk_02 + sp18[0]));
            arg1->unk_06 = (u16) ((u16) D_800E3DA8[1] + (temp_s2->unk_06 + sp18[1]));
            temp_a0 = ((S_800AC82C_7 *)((*(void **)((u8 *)arg3 + 0x60))))->unk_88;
            (*(u16 *)((u8 *)arg3 + 0x88)) = temp_a0;
            arg0->unk_92 = (s16) (((temp_s2->unk_0A + sp18[2]) - temp_a0) + 8);
            arg2->unk_06 = 0x10;
            (*(volatile s32 *)((u8 *)arg3 + 0x1C)) = (s32) ((*(s32 *)((u8 *)arg3 + 0x1C)) | 0x40000000);
            temp_v0_5 = (*(void * volatile *)((u8 *)arg3 + 0x60));
            temp_v1_2 = (*(s16 *)((u8 *)arg3 + 0x6A));
            temp_parent_u16 = temp_v0_5->unk_2A.v;
            temp_a1_2 = temp_v0_5->unk_2A.n;
            temp_v0_6 = (*(u16 *)((u8 *)arg3 + 0x2A)) - (temp_v1_2 - temp_a1_2);
            (*(u16 *)((u8 *)arg3 + 0x6A)) = temp_parent_u16;
            (*(s16 *)((u8 *)arg3 + 0x2A)) = temp_v0_6;
        }
        return 0;
    }
    return 0;
}
