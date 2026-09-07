#include "common.h"
#include "m2c_compat.h"

typedef struct S_800250C0_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    u8 pad_0E[0x12];
    s16 unk_20;
    u8 pad_22[0x8];
    u8 unk_2A;
    u8 unk_2B;
} S_800250C0_0;   /* arg0 in func_800250C0; pointer addresses record offset 0x2 */

typedef struct S_800250C0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800250C0_1;   /* arg2 in func_800250C0 */


extern s16 D_80026428[];
extern s32 D_800814A0[3];
extern void *D_80024008[];

void func_800250C0(void *arg0, s32 arg1, S_800250C0_1 *arg2, s32 arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    void **jump_table;
    s32 temp_v1;
    s32 temp_lo;
    s32 result;

    arg1 = ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_06;
    arg3 = ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_0C;
    D_80026428[0] = 1;
    if (arg1 < arg3) {
        temp_lo = arg1 * 3;
        goto block_4;
    }
    temp_v1 = ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_04;
    temp_v1 -= arg1;
    temp_lo = temp_v1 * 3;
block_4:
    result = (temp_lo * 0x10) / arg3;
    arg2->unk_0E = (s8) result;
    arg2->unk_0D = (s8) result;
    arg2->unk_0C = (s8) result;
    temp_v1 = ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_20;
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_06 = (s16) ((u16) ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_06 + 1);
    if ((u32) temp_v1 >= 8U) {
        goto block_10;
    }
    jump_table = D_80024008;
    (void)jt_keep; goto *jump_table[(u32)(temp_v1)];
jt_c0:
jt_c1:
jt_c2:
jt_c4:
jt_c5:
jt_c6:
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_20 = (s16) ((u16) ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_20 + 1);
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2A = (u8) (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2A + 0x10);
    goto block_10;
jt_c3:
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_20 = (s16) ((u16) ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_20 + 1);
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2A = (u8) (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2A - 0x30);
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2B = (u8) (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2B + 0x20);
    goto block_10;
jt_c7:
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_20 = 0;
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2A = (u8) (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2A - 0x30);
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2B = (u8) (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_2B - 0x20);
block_10:
    if (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_06 < ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_04) {
        goto block_12;
    }
    ((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800250C0_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
block_12:
    return;
}
