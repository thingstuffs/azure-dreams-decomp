#include "common.h"
#include "m2c_compat.h"

typedef struct S_8189E820_0_pre {
    u16 unk_00;
} S_8189E820_0_pre;   /* the 0x2 bytes before arg0 in func_8189E820, addressed as arg0[-1] */

typedef struct S_8189E820_0 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    void * unk_08;
} S_8189E820_0;   /* arg0 in func_8189E820 */

typedef struct S_8189E820_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8189E820_1;   /* temp_v1 in func_8189E820 */

typedef struct S_8189E820_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8189E820_2;   /* arg1 in func_8189E820 */

typedef struct S_8189E820_3 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_8189E820_3;   /* arg2 in func_8189E820 */

s32 func_800644B8();
extern s32 D_800814A0[3];

void func_8189E820(void *arg0, S_8189E820_2 *arg1, S_8189E820_3 *arg2)
{
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_a0_2;
    s32 temp_v1_2;
    s32 temp_a1;
    S_8189E820_1 *temp_v1;

    temp_v1 = ((S_8189E820_0 *)arg0)->unk_08;
    temp_v1->unk_14 =
        (u16)(temp_v1->unk_14 + 1);
    temp_v0_2 = arg1->unk_00;
    temp_a0_2 = arg1->unk_0C;
    temp_v1_2 = arg1->unk_04;
    temp_a1 = arg1->unk_10;
    arg1->unk_00 = temp_v0_2 + temp_a0_2;
    arg1->unk_04 = temp_v1_2 + temp_a1;
    ((S_8189E820_0 *)arg0)->unk_04 =
        ((S_8189E820_0 *)arg0)->unk_04 + arg1->unk_14;
    arg1->unk_08 =
        ((S_8189E820_0 *)arg0)->unk_04 -
        ((func_800644B8((0x800 / (s16)((S_8189E820_0 *)arg0)->unk_02) *
                        ((S_8189E820_0 *)arg0)->unk_00,
                        temp_a1) >> 4) * 0xC000);
    arg2->unk_1A =
        (u16)(arg2->unk_1A + 0x300);
    temp_v0 = (u16)((S_8189E820_0 *)arg0)->unk_00 + 1;
    ((S_8189E820_0 *)arg0)->unk_00 = temp_v0;
    if (((S_8189E820_0 *)arg0)->unk_02 < temp_v0) {
        ((S_8189E820_0_pre *)arg0)[-1].unk_00 =
            (u16)(((S_8189E820_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
