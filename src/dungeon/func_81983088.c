#include "common.h"

typedef struct S_80024888_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024888_0;   /* arg1 in func_80024888 */

typedef struct S_80024888_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024888_1;   /* arg2 in func_80024888 */

typedef struct S_80024888_2_pre {
    u16 unk_00;
} S_80024888_2_pre;   /* the 0x2 bytes before arg0 in func_80024888, addressed as arg0[-1] */

typedef struct S_80024888_2 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_80024888_2;   /* arg0 in func_80024888 */


extern u16 D_800269F8[];
extern s32 D_800814A0[];


void func_80024888(void *arg0, S_80024888_0 *arg1, S_80024888_1 *arg2) {
    s32 temp_a0;
    s32 temp_a3;
    u16 temp_v0_global;
    u8 temp_v0;
    u8 temp_v0_2;
    u16 temp_v0_3;

    temp_v0_global = D_800269F8[0];
    temp_a0 = arg1->unk_0C;
    temp_a3 = arg1->unk_10;
    D_800269F8[0] = temp_v0_global + 1;
    arg1->unk_00 = arg1->unk_00 + temp_a0;
    arg1->unk_04 = arg1->unk_04 + temp_a3;
    arg1->unk_08 = arg1->unk_08 + arg1->unk_14;
    arg1->unk_14 = arg1->unk_14 + 0x2000;
    temp_v0 = arg2->unk_0C;
    temp_v0_2 = temp_v0 - (temp_v0 >> 4);
    arg2->unk_0C = temp_v0_2;
    arg2->unk_0D = temp_v0_2;
    arg2->unk_0E = temp_v0_2;
    temp_v0_3 = ((S_80024888_2 *)arg0)->unk_30 - 1;
    ((S_80024888_2 *)arg0)->unk_30 = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        ((S_80024888_2_pre *)arg0)[-1].unk_00 = ((S_80024888_2_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
