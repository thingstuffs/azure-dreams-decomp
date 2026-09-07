#include "common.h"

typedef struct S_7FFE7BE8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x1C];
    s32 unk_2C;
    u8 pad_30[0x14];
    void * unk_44;
} S_7FFE7BE8_0;   /* arg0 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_7FFE7BE8_1;   /* temp_a0 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE7BE8_2;   /* temp_v1 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_7FFE7BE8_3;   /* arg2 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_7FFE7BE8_4;   /* temp_a0_2 in func_7FFE7BE8 */

typedef struct S_7FFE7BE8_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_7FFE7BE8_5;   /* arg1 in func_7FFE7BE8 */



extern void func_70040A18(void *, void *);
extern void func_7003A7C4(void *, void *, s32);
extern s32 D_8004136C;
extern s32 D_800E2BB8;

void func_7FFE7BE8(S_7FFE7BE8_0 *arg0, S_7FFE7BE8_5 *arg1, S_7FFE7BE8_3 *arg2)
{
    S_7FFE7BE8_1 *temp_a0;
    S_7FFE7BE8_4 *temp_a0_2;
    S_7FFE7BE8_2 *temp_v1;
    s32 copied_value;
    u16 flags;

    arg0->unk_44 = arg1;
    func_70040A18(arg0, &D_8004136C);
    temp_a0 = arg0->unk_0C;
    temp_a0->unk_10 = 0x20;
    temp_a0->unk_14 = temp_a0->unk_14 | 0xC;
    temp_v1 = arg0->unk_08;
    temp_v1->unk_02 = arg2->unk_02;
    temp_v1->unk_06 = arg2->unk_06;
    temp_v1->unk_0A = arg2->unk_0A;
    temp_a0_2 = arg0->unk_0C;
    temp_a0_2->unk_1E = 0x800;
    temp_a0_2->unk_1C = 0x800;
    arg0->unk_2C = arg1->unk_0C;
    copied_value = arg1->unk_0C;
    flags = temp_a0_2->unk_14;
    temp_a0_2->unk_12 = 0x7DCF;
    flags |= 0x100;
    temp_a0_2->unk_0C = copied_value;
    temp_a0_2->unk_14 = flags;
    func_7003A7C4(temp_a0_2, &D_800E2BB8, 0);
}
