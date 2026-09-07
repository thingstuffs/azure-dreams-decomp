#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D4CB0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4CB0_0;   /* arg1 in func_800D4CB0 */

typedef struct S_800D4CB0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800D4CB0_1;   /* arg2 in func_800D4CB0 */

typedef struct S_800D4CB0_2_pre {
    u16 unk_00;
} S_800D4CB0_2_pre;   /* the 0x2 bytes before arg0 in func_800D4CB0, addressed as arg0[-1] */

typedef struct S_800D4CB0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xF];
    s16 unk_1E;
    s16 unk_20;
} S_800D4CB0_2;   /* arg0 in func_800D4CB0 */


extern M2C_UNK D_800814A0;

void func_800D4CB0(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0;

    ((S_800D4CB0_0 *)arg1)->unk_00 += ((S_800D4CB0_0 *)arg1)->unk_0C;
    ((S_800D4CB0_0 *)arg1)->unk_04 += ((S_800D4CB0_0 *)arg1)->unk_10;
    ((S_800D4CB0_0 *)arg1)->unk_08 += ((S_800D4CB0_0 *)arg1)->unk_14;
    ((S_800D4CB0_0 *)arg1)->unk_0C /= 2;
    ((S_800D4CB0_0 *)arg1)->unk_10 /= 2;
    ((S_800D4CB0_0 *)arg1)->unk_14 /= 2;
    ((S_800D4CB0_1 *)arg2)->unk_0C = (s8) ((s32) (((S_800D4CB0_2 *)arg0)->unk_0C * ((S_800D4CB0_2 *)arg0)->unk_1E) / (s16) ((S_800D4CB0_2 *)arg0)->unk_20);
    ((S_800D4CB0_1 *)arg2)->unk_0D = (s8) ((s32) (((S_800D4CB0_2 *)arg0)->unk_0D * ((S_800D4CB0_2 *)arg0)->unk_1E) / (s16) ((S_800D4CB0_2 *)arg0)->unk_20);
    ((S_800D4CB0_1 *)arg2)->unk_0E = (s8) ((s32) (((S_800D4CB0_2 *)arg0)->unk_0E * ((S_800D4CB0_2 *)arg0)->unk_1E) / (s16) ((S_800D4CB0_2 *)arg0)->unk_20);
    temp_v0 = (u16) ((S_800D4CB0_2 *)arg0)->unk_1E - 1;
    ((S_800D4CB0_2 *)arg0)->unk_1E = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_800D4CB0_2_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; arg0 stays in t0 while six signed fields use natural in-place updates.
   Compound assignments retain the +0x10 value and reproduce retail's load/store emission order.
   Direct D_800814A0 access removes one address-add word and closes the branch displacement cascade. */
